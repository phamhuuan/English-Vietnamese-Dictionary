static char code[128] = {0};
GtkListStore *list;

int prefix(const char *big, const char *small);
int btfind(char *word, BTA* file);
int commond_char(char * str1, char * str2, int start);
void jrb_to_list(JRB nextWordArray);
int insert_insoundexlist(char *soundexlist , char *newword,  char *word, char *soundexWord);
static void search(GtkWidget *w, gpointer data);
void suggest(char * word, gboolean Tab_pressed);
gboolean search_suggest(GtkWidget * entry, GdkEvent * event, gpointer No_need);
static void edit(GtkWidget *w, gpointer data);
void addRemoveLibrary(GtkWidget *w, gpointer data);
void searchWord(GtkWidget widget, gpointer window);

const char* soundex(const char *s){
	static char out[5];
	int c, prev, i;

	out[0] = out[4] = 0;
	if(!s || !*s) return out;

	out[0] = *s++;

	/* first letter, though not coded, can still affect next letter: Pfister */
	prev = code[(int)out[0]];
	for(i = 1; *s && i < 4; s++){
		if((c = code[(int) * s]) == prev) continue;
		if(c == -1) prev = 0;	/* vowel as separator */
		else if(c > 0){
			out[i++] = c + '0';
			prev = c;
		}
	}
	while(i < 4) out[i++] = '0';
	return out;
}

int prefix(const char *big, const char *small){// tra lai 1 neu giong prefix, 0 neu nguoc lai
	int small_len = strlen(small);
	int big_len = strlen(big);
	int i;
	if(big_len < small_len)
		return 0;
	for(i = 0; i < small_len; i++)
		if(big[i] != small[i])
			return 0;
	return 1;    
}

int commond_char(char * str1, char * str2, int start){
	int i;
	int slen1 = strlen(str1);
	int slen2 = strlen(str2);
	int slen  = (slen1 < slen2) ? slen1 : slen2;
	for( i = start; i < slen; i++)
		if(str1[i] != str2[i])
			return i;
	return i;
}

void jrb_to_list(JRB nextWordArray){
   	GtkTreeIter Iter;
   	JRB tmp;
   	int max = 8;
   	jrb_traverse(tmp, nextWordArray){
     	gtk_list_store_append(GTK_LIST_STORE(list), &Iter);
    	gtk_list_store_set(GTK_LIST_STORE(list), &Iter, 0, jval_s(tmp->key), -1 );
 		if(max-- < 1)
   			return;
    }
}

int insert_insoundexlist(char *soundexlist , char *newword,  char *word, char *soundexWord){// tao newword voi ma soundex
	if(strcmp(soundexWord, soundex(newword)) == 0){
		if(strcmp(newword, word) != 0){
			strcat(soundexlist, newword);
			strcat(soundexlist, "\n");
			return 1;
		}
	}
	return 0;
}

void suggest(char * word, gboolean Tab_pressed){// suggest, dua vao prefix, dung JRB to list ~
	char nextword[100], prevword[100];
	int i, NumOfCommondChar, minNumOfCommondChar = 1000;
	int max;
	GtkTreeIter Iter;
	JRB tmp, nextWordArray = make_jrb();
	BTint value, existed = 0;
	strcpy(nextword, word);
	int wordlen = strlen(word);
	gtk_list_store_clear(GTK_LIST_STORE(list));
	if(bfndky(dictionary, word, &value) ==  0){ // tim word trong dictionary, value la gia tri cua 'word' tim duoc
		existed = 1;
		gtk_list_store_append(GTK_LIST_STORE(list), &Iter);
		gtk_list_store_set(GTK_LIST_STORE(list), &Iter, 0, nextword, -1 ); // neu dung thi ok
	}
	if(!existed)
		btins(dictionary, nextword, "", 1); // chen key va data vao B-tree, o lay chen blank vao !

	for(i = 0; i < 1945; i++){
		bnxtky(dictionary, nextword, &value);  // tim 'key' tiep theo
		if(prefix(nextword, word)){ // tim nhung tu co prefix giong
			jrb_insert_str(nextWordArray, strdup(nextword), JNULL);  // va chen vao array nextword (de show ra list -> jrb_to_list)
		}
		else break;
	}

	if(!existed && Tab_pressed){// an tab de ra tu goi y xD!
		if(jrb_empty(nextWordArray)){
			char soundexlist[1000] = "Ý bạn là:\n";
			char soundexWord[50];
			strcpy(nextword, word);
			strcpy(prevword, word);
			strcpy(soundexWord, soundex(word)); // soundex dung de tim tu 'xung quanh'
			max = 5;
			for(i = 0; (i < 10000) && max; i++){
				if(bprvky(dictionary , prevword, &value) == 0)
					if(insert_insoundexlist(soundexlist, prevword, word, soundexWord))
						max--;
			}
			max = 5;
			for(i = 0; (i < 10000) && max; i++){
				if(bnxtky(dictionary, nextword, &value) == 0)
					if(insert_insoundexlist(soundexlist, nextword, word, soundexWord))
						max--;
			}
			setTextView(soundexlist, GTK_TEXT_VIEW(textView));
		}
		else{
			strcpy(nextword, jval_s(jrb_first(nextWordArray)->key));
			jrb_traverse(tmp, nextWordArray){
				NumOfCommondChar = commond_char(nextword, jval_s(tmp->key), wordlen);
				if(minNumOfCommondChar > NumOfCommondChar)
					minNumOfCommondChar = NumOfCommondChar;
			}

			if((minNumOfCommondChar != 1000) && (minNumOfCommondChar > wordlen)) {
				nextword[NumOfCommondChar] = '\0';
				gtk_entry_set_text(GTK_ENTRY(entry_search), nextword);
				gtk_editable_set_position(GTK_EDITABLE(entry_search), NumOfCommondChar);
			}
		}
	}
	else
		jrb_to_list(nextWordArray);
	if(!existed)
		btdel(dictionary, word);
	jrb_free_tree(nextWordArray);
}

gboolean search_suggest(GtkWidget * entry, GdkEvent * event, gpointer No_need){// gioi han ky tu, chi nhan alphabelt va tab
	GdkEventKey *keyEvent = (GdkEventKey*)event;
	char word[50];
	int len;
	strcpy(word, gtk_entry_get_text(GTK_ENTRY(entry_search)));
	if(keyEvent->keyval == GDK_KEY_Tab) suggest(word, TRUE);
	else{
		if(keyEvent->keyval != GDK_KEY_BackSpace) {
			len = strlen(word);
			word[len] = keyEvent->keyval;
			word[len + 1] = '\0';
		}
		else{
			len = strlen(word);
			word[len - 1] = '\0';
		}
		suggest(word, FALSE);
	}
	return FALSE;
}

static void search(GtkWidget *w, gpointer data){
	GtkWidget *entry1 = ((GtkWidget**)data)[0];
	GtkWidget *window1 = ((GtkWidget**)data)[1];
	GtkWidget *button4 = ((GtkWidget**)data)[3];

	a = gtk_entry_get_text(GTK_ENTRY(entry1));
	char word[50];
	BTint x;

	strcpy(word, a);
	if(word[0] == '\0')
		Message(GTK_WIDGET(window1), GTK_MESSAGE_WARNING, "Warning!", "Input is left blank!");
	else{
		int result = btfind(word, dictionary);
		if(result == 0)
			Message(GTK_WIDGET(window1), GTK_MESSAGE_ERROR, "Error!","Word not found!");
	}

	if(bfndky(libraryTree, word, &x) != 0) gtk_button_set_label(GTK_BUTTON(button4), "Add to library");
	else gtk_button_set_label(GTK_BUTTON(button4), "Remove from library");

	
	//Luu vao file history

	if(bfndky(historyTree, word, &x) != 0)
		binsky(historyTree, word, 0);

	// btsel(dictionary, word, mean, 100000, &size);
	// g_print("%d\n",btins(historyTree, word, mean, strlen(mean) + 1));

	for(int i = 0; i < strlen(word); i++) if(word[i] == ' ') word[i] = '_';
	
	fileHistory = fopen("../data/history.dat", "ab");fprintf(fileHistory, "%s\n", word);fclose(fileHistory);

	fileHistory = fopen("../data/history.dat", "rb");
	linkedList = new_dllist();int temp = 0;
	while(fscanf(fileHistory, "%s", wordHistory) != EOF){
		strcpy(wordTmp[temp++], wordHistory);//g_print("%s\n", wordHistory);
	}
	fclose(fileHistory);
	for(int i = 0; i < temp; i++) dll_append(linkedList, new_jval_s(wordTmp[i]));

	dll_traverse(node, linkedList)
		if(strcmp(jval_s(node->val), word) == 0 && node != linkedList->blink){
			dll_delete_node(node);
			break;
		}
	fileHistory = fopen("../data/history.dat", "wb");
	dll_traverse(node, linkedList)
		fprintf(fileHistory, "%s\n", jval_s(node->val));
	fclose(fileHistory);
	free_dllist(linkedList);

	return;
}

int btfind(char *word, BTA* file){// dung cho ham search
	char mean[100000];

	if(btsel(file, word, mean, 100000, &size) == 0){
		setTextView(mean, GTK_TEXT_VIEW(textView));
		return 1;
	}
    else
    	return 0;
}

static void edit(GtkWidget *w, gpointer data){// ham chuc nang edit
	GtkWidget *entry1= ((GtkWidget**)data)[0];
	GtkWidget *window1=((GtkWidget**)data)[1];
	GtkWidget *edit_view=((GtkWidget**)data)[2];

	BTint x;

	if(gtk_entry_get_text(GTK_ENTRY(entry1))[0] == 0 || bfndky(dictionary, (char*)gtk_entry_get_text(GTK_ENTRY(entry1)), &x) != 0){
		Message(window1, GTK_MESSAGE_WARNING, "Warning", "Input is left blank!"); // Message o tren
		return;
	}

	a = gtk_entry_get_text(GTK_ENTRY(entry1));
	char word[50],mean[100000];
	strcpy(word,a);

	GtkTextBuffer *buffer2;
	GtkTextIter start, end, iter;

	buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(edit_view));//
	gtk_text_buffer_get_iter_at_offset(buffer2, &iter, 0);

	gtk_text_buffer_insert(buffer2, &iter, "", -1);
	gtk_text_buffer_get_bounds(buffer2, &start, &end);
	b = gtk_text_buffer_get_text(buffer2, &start, &end, FALSE);

	strcpy(mean,b);

	if(word[0] == '\0' || mean[0] == '\0')
		Message(GTK_WIDGET(window1), GTK_MESSAGE_WARNING, "Warning!", "No part is left blank!");
	else if(bfndky(dictionary, word, &x ) != 0)
		Message(GTK_WIDGET(window1), GTK_MESSAGE_ERROR, "Error", "Word not found!");
	else{
		if(btupd(dictionary, word, mean, strlen(mean) + 1) == 1)
			Message(GTK_WIDGET(window1),GTK_MESSAGE_ERROR, "Error","Can not update!");
		else
			Message(GTK_WIDGET(window1),GTK_MESSAGE_INFO, "Success!","Updated!");
	}
}

void addRemoveLibrary(GtkWidget *w, gpointer data){
	GtkWidget *entry1 = ((GtkWidget**)data)[0];
	GtkWidget *window1 =((GtkWidget**)data)[1];
	GtkWidget *button4 = ((GtkWidget**)data)[3];

	BTint x;
	a = gtk_entry_get_text(GTK_ENTRY(entry1));
	char word[50];
	strcpy(word,a);

	if(word[0] == '\0'){
		Message(GTK_WIDGET(window1), GTK_MESSAGE_WARNING, "Warning!", "No part is left blank!");
		return;
	}

	if(bfndky(libraryTree, word, &x) != 0){
		binsky(libraryTree, word, 0);
		gtk_button_set_label(GTK_BUTTON(button4), "Remove from library");
		Message(GTK_WIDGET(window1),GTK_MESSAGE_INFO, "Success!","Added!");
	}
	else{
		bdelky(libraryTree, word);
		gtk_button_set_label(GTK_BUTTON(button4), "Add to library");
		Message(GTK_WIDGET(window1),GTK_MESSAGE_INFO, "Success!","Removed!");
	}
}

void searchWord(GtkWidget widget, gpointer window){
	GtkWidget *fixed, *image;
	GtkWidget *button1,*window1,*label,*button2,*button3,*button4,*label2;

	myCSS();

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	if(theme == 1) gtk_widget_set_name(window1, "window1");
	if(theme == 1) gtk_widget_set_name(window1, "window1Theme2");
	gtk_window_set_title(GTK_WINDOW(window1), "Search");
	gtk_window_set_default_size(GTK_WINDOW(window1), 750, 430);
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window1), fixed);

	label = gtk_label_new("Input:");
	gtk_fixed_put(GTK_FIXED(fixed), label, 30, 30);

	entry_search = gtk_entry_new();
	gtk_widget_set_size_request(entry_search, 300, 30);
	gtk_fixed_put(GTK_FIXED(fixed), entry_search, 100, 25);
	gtk_entry_set_max_length(GTK_ENTRY(entry_search), 50);
	if(theme == 1) gtk_widget_set_name(entry_search, "entry_search");
	if(theme == 2) gtk_widget_set_name(entry_search, "entry_searchTheme2");

	GtkEntryCompletion *comple = gtk_entry_completion_new();
	gtk_entry_completion_set_text_column(comple, 0);
	list = gtk_list_store_new(10, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	gtk_entry_completion_set_model(comple, GTK_TREE_MODEL(list));
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry_search), "Enter word here");
	gtk_entry_set_completion(GTK_ENTRY(entry_search), comple);

	button1 = gtk_button_new_with_label("Search");
	if(theme == 1) gtk_widget_set_name(button1, "buttonSearch");
	if(theme == 2) gtk_widget_set_name(button1, "buttonSearchTheme2");
	gtk_fixed_put(GTK_FIXED(fixed), button1, 450, 15);
	gtk_widget_set_size_request(button1, 90, 30);

	label2 = gtk_label_new("Meaning:");
	gtk_fixed_put(GTK_FIXED(fixed), label2, 30, 200);

	GtkWidget *scrolling = gtk_scrolled_window_new(NULL, NULL);
	gtk_fixed_put(GTK_FIXED(fixed), scrolling, 100, 100);
	gtk_widget_set_size_request(scrolling, 300, 300);

	textView = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scrolling), textView);
	if(theme == 1) gtk_widget_set_name(textView, "textView");
	if(theme == 2) gtk_widget_set_name(textView, "entry_searchTheme2");

	button2 = gtk_button_new_with_label("Back");
	if(theme == 1) gtk_widget_set_name(button2, "buttonBack");
	if(theme == 2) gtk_widget_set_name(button2, "buttonSearchTheme2");
	gtk_fixed_put(GTK_FIXED(fixed), button2, 560, 15);
	gtk_widget_set_size_request(button2, 90, 30);

	button4 = gtk_button_new();
	if(theme == 1) gtk_widget_set_name(button4, "buttonSave");
	if(theme == 2) gtk_widget_set_name(button4, "buttonSearchTheme2");
	gtk_fixed_put(GTK_FIXED(fixed), button4, 450, 50);
	gtk_widget_set_size_request(button4, 200, 30);

	button3 = gtk_button_new_with_label("Update meaning");
	if(theme == 1) gtk_widget_set_name(button3, "buttonUpt");
	if(theme == 2) gtk_widget_set_name(button3, "buttonSearchTheme2");
	gtk_fixed_put(GTK_FIXED(fixed), button3, 450, 85);
	gtk_widget_set_size_request(button3, 200, 30);

	if(theme == 1) image = gtk_image_new_from_file("../Img/kaori.jpg");
	if(theme == 2) image = gtk_image_new_from_file("../Img/tfwb2.jpg");
	gtk_fixed_put(GTK_FIXED(fixed), image, 450, 125);

	GtkWidget *data[4];
	data[0] = entry_search;
	data[1] = window1;
	data[2] = textView;
	data[3] = button4;

	g_signal_connect(entry_search, "key-press-event", G_CALLBACK(search_suggest), NULL);
	g_signal_connect(G_OBJECT(entry_search), "activate", G_CALLBACK(search), data);//khi nhap tu xong an enter thi search
	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(search), data);
	g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(close_window), window1);
	g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(edit), data);
	g_signal_connect(G_OBJECT(button4), "clicked", G_CALLBACK(addRemoveLibrary), data);
	g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window1);
	gtk_main();

	return;
}