GtkWidget *fixed /*, *image*/;
GtkWidget *button1,*window1,*label,*button2,*button3,*button4,*button5,*label2;

void history();
void historySuggest(GtkWidget * entry, GdkEvent * event, gpointer data);
void suggestHistory(char *word, gboolean Tab_pressed);
void delete(GtkWidget *w, gpointer data);
void deleteAll(GtkWidget *w, gpointer data);
void showAll(GtkWidget *w, gpointer data);
void searchHistory(GtkWidget *w, gpointer data);

void suggestHistory(char *word, gboolean Tab_pressed){
	char nextword[100];
	GtkTreeIter Iter;
	strcpy(nextword, word);
	gtk_list_store_clear(GTK_LIST_STORE(list));
    if(word[0] != '\0'){int j;
        fileHistory = fopen("../data/history.dat", "rb");
        while(fscanf(fileHistory, "%s", wordHistory) != EOF){
            for(j = 0; j < strlen(wordHistory); j++) if(wordHistory[j] == '_') wordHistory[j] = ' ';
			gtk_list_store_append(list, &Iter);
			gtk_list_store_set(list, &Iter, 0, wordHistory, -1);
        }
    }
}

void historySuggest(GtkWidget * entry, GdkEvent * event, gpointer data){// gioi han ky tu, chi nhan alphabelt va tab
	GdkEventKey *keyEvent = (GdkEventKey*)event;
	GtkWidget *textView = ((GtkWidget**)data)[2];
	char word[50];//text entry nhap nhieu qua se bi loi vi tran bo nho cua bien word trong ham nay va newWord, prevWord o ham suggestHistory
	int len;
	setTextView("", GTK_TEXT_VIEW(textView));
	strcpy(word, gtk_entry_get_text(GTK_ENTRY(entry_search)));
	if(keyEvent->keyval == GDK_KEY_Tab) suggestHistory(word, TRUE);
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
		suggestHistory(word, FALSE);
	}
}

void delete(GtkWidget *w, gpointer data){
	GtkWidget *entry1 = ((GtkWidget**)data)[0];
	GtkWidget *window1 = ((GtkWidget**)data)[1];

	a = gtk_entry_get_text(GTK_ENTRY(entry1));
	char word[50];

	strcpy(word, a);

	if(word[0] == '\0'){
		Message(GTK_WIDGET(window1),GTK_MESSAGE_ERROR, "ERROR!","Input blank empty!");
		return;
	}
	fileHistory = fopen("../data/history.dat", "rb");
	linkedList = new_dllist();int temp = 0;
	while(fscanf(fileHistory, "%s", wordHistory) != EOF){
		strcpy(wordTmp[temp++], wordHistory);
	}
	fclose(fileHistory);
	for(int i = 0; i < temp; i++) dll_append(linkedList, new_jval_s(wordTmp[i]));

	dll_traverse(node, linkedList)
		if(strcmp(jval_s(node->val), word) == 0){
			dll_delete_node(node);
			break;
		}
	fileHistory = fopen("../data/history.dat", "wb");
	dll_traverse(node, linkedList)
		fprintf(fileHistory, "%s\n", jval_s(node->val));
	fclose(fileHistory);
	free_dllist(linkedList);
	Message(GTK_WIDGET(window1),GTK_MESSAGE_INFO, "Success!","Removed!");
}

void deleteAll(GtkWidget *w, gpointer data){
	GtkWidget *window1 = ((GtkWidget**)data)[1];

	fileHistory = fopen("../data/history.dat", "w+b");
	fclose(fileHistory);
	Message(GTK_WIDGET(window1),GTK_MESSAGE_INFO, "Success!","Removed!");
}

void showAll(GtkWidget *w, gpointer data){
	GtkWidget *textView = ((GtkWidget**)data)[2];
	char showAllResult[10000];showAllResult[0] = '\0';
	gtk_label_set_text(GTK_LABEL(label2), "History:");

	fileHistory = fopen("../data/history.dat", "rb");
	int temp = 0;
	while(fscanf(fileHistory, "%s", wordHistory) != EOF){
		for(int i = 0; i < strlen(wordHistory); i++) if(wordHistory[i] == '_') wordHistory[i] = ' ';
		strcpy(wordTmp[temp++], wordHistory);
	}
	fclose(fileHistory);
	for(int i = temp - 1; i >= 0; i--){
		strcat(showAllResult, wordTmp[i]);
		strcat(showAllResult, "\n");
	}

	setTextView(showAllResult, GTK_TEXT_VIEW(textView));
}

void searchHistory(GtkWidget *w, gpointer data){
	GtkWidget *entry1 = ((GtkWidget**)data)[0];
	GtkWidget *window1 = ((GtkWidget**)data)[1];

	a = gtk_entry_get_text(GTK_ENTRY(entry1));
	gtk_label_set_text(GTK_LABEL(label2), "Meaning:");
	char word[50], tmp[50], mean[100000];
	int check = 0;

	strcpy(word, a);
	if(word[0] == '\0')
		Message(GTK_WIDGET(window1), GTK_MESSAGE_WARNING, "Warning!", "Input is left blank!");
	else{
		for(int i = 0; i < strlen(word); i++) if(word[i] == ' ') word[i] = '_';
		fileHistory = fopen("../data/history.dat", "rb");
		while(fscanf(fileHistory, "%s", tmp) != EOF){
			if(strcmp(tmp, word) == 0){
				for(int i = 0; i < strlen(word); i++) if(word[i] == '_') word[i] = ' ';
				if(btsel(dictionary, word, mean, 100000, &size) == 0){
					setTextView(mean, GTK_TEXT_VIEW(textView));
				}
				check = 1;
			}
		}	
		if(check == 0) Message(GTK_WIDGET(window1), GTK_MESSAGE_ERROR, "Error!", "Word not found!");
	}
}

void history(){
	fileIsLogIn = fopen("../data/isLogin.dat", "rb");
    char tmp[50];
    fscanf(fileIsLogIn, "%d %s", &isLogin, tmp);
    fclose(fileIsLogIn);
    if(isLogin == 0){
        Message(GTK_WIDGET(window),GTK_MESSAGE_INFO, "Notice","You need login to use this function");
        return;
    }
	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(window1, "windowHistory");
	gtk_window_set_title(GTK_WINDOW(window1), "History");
	gtk_window_set_default_size(GTK_WINDOW(window1), 750, 430);
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window1), FALSE);

	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window1), fixed);

	label = gtk_label_new("Input:");
	gtk_fixed_put(GTK_FIXED(fixed), label, 30, 30);

	entry_search = gtk_entry_new();
	gtk_widget_set_size_request(entry_search, 300, 30);
	gtk_fixed_put(GTK_FIXED(fixed), entry_search, 100, 25);
	gtk_entry_set_max_length(GTK_ENTRY(entry_search), 50);
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry_search), "Enter word here");
	if(theme == 1) gtk_widget_set_name(entry_search, "entry_search_history");
	if(theme == 2) gtk_widget_set_name(entry_search, "entry_search_history");

	GtkEntryCompletion *comple = gtk_entry_completion_new();
	gtk_entry_completion_set_text_column(comple, 0);
	list = gtk_list_store_new(10, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	gtk_entry_completion_set_model(comple, GTK_TREE_MODEL(list));
	gtk_entry_set_completion(GTK_ENTRY(entry_search), comple);

	button1 = gtk_button_new_with_label("Search");
	if(theme == 1) gtk_widget_set_name(button1, "buttonSearchHistory");
	if(theme == 2) gtk_widget_set_name(button1, "buttonSearchHistory");
	gtk_fixed_put(GTK_FIXED(fixed), button1, 450, 15);
	gtk_widget_set_size_request(button1, 90, 30);

	label2 = gtk_label_new("");
	gtk_fixed_put(GTK_FIXED(fixed), label2, 30, 200);

	GtkWidget *scrolling = gtk_scrolled_window_new(NULL, NULL);
	gtk_fixed_put(GTK_FIXED(fixed), scrolling, 100, 100);
	gtk_widget_set_size_request(scrolling, 300, 300);

	textView = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scrolling), textView);
	if(theme == 1) gtk_widget_set_name(textView, "entry_search_history");
	if(theme == 2) gtk_widget_set_name(textView, "entry_search_history");

	button2 = gtk_button_new_with_label("Back");
	if(theme == 1) gtk_widget_set_name(button2, "buttonSearchHistory");
	if(theme == 2) gtk_widget_set_name(button2, "buttonSearchHistory");
	gtk_fixed_put(GTK_FIXED(fixed), button2, 560, 15);
	gtk_widget_set_size_request(button2, 90, 30);

	button4 = gtk_button_new_with_label("Show all");
	if(theme == 1) gtk_widget_set_name(button4, "buttonSearchHistory");
	if(theme == 2) gtk_widget_set_name(button4, "buttonSearchHistory");
	gtk_fixed_put(GTK_FIXED(fixed), button4, 450, 50);
	gtk_widget_set_size_request(button4, 200, 30);

	button3 = gtk_button_new_with_label("Delete");
	if(theme == 1) gtk_widget_set_name(button3, "buttonSearchHistory");
	if(theme == 2) gtk_widget_set_name(button3, "buttonSearchHistory");
	gtk_fixed_put(GTK_FIXED(fixed), button3, 450, 85);
	gtk_widget_set_size_request(button3, 90, 30);

	button5 = gtk_button_new_with_label("Delete all");
	if(theme == 1) gtk_widget_set_name(button5, "buttonSearchHistory");
	if(theme == 2) gtk_widget_set_name(button5, "buttonSearchHistory");
	gtk_fixed_put(GTK_FIXED(fixed), button5, 560, 85);
	gtk_widget_set_size_request(button5, 90, 30);

	if(theme == 1) image = gtk_image_new_from_file("../Img/kaori13.jpg");
	if(theme == 2) image = gtk_image_new_from_file("../Img/tfwb9.jpg");
	gtk_fixed_put(GTK_FIXED(fixed), image, 450, 125);

	GtkWidget *data[4];
	data[0] = entry_search;
	data[1] = window1;
	data[2] = textView;
	data[3] = button4;

	g_signal_connect(entry_search, "key-press-event", G_CALLBACK(historySuggest), data);
	g_signal_connect(G_OBJECT(entry_search), "activate", G_CALLBACK(searchHistory), data);//khi nhap tu xong an enter thi search
	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(searchHistory), data);
	g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(close_window), window1);
	g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(delete), data);
	g_signal_connect(G_OBJECT(button4), "clicked", G_CALLBACK(showAll), data);
	g_signal_connect(G_OBJECT(button5), "clicked", G_CALLBACK(deleteAll), data);
	g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window1);
	gtk_main();

	return;
}