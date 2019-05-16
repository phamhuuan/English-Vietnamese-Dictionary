GtkWidget *window2;
GtkListStore *list;
GtkWidget *fixed, *image;
GtkWidget *button1,*window1,*label,*entry,*button2;

void del(GtkWidget *w, gpointer data);
void deleteWord(GtkWidget widget, gpointer window);
void cfdel(GtkWidget *w, gpointer data);
void delSuggest(GtkWidget *entry, GdkEvent *event);
void suggestDel(char * word, gboolean Tab_pressed);

void suggestDel(char * word, gboolean Tab_pressed){
	char nextword[100], tmpword[100];
	int max;
	GtkTreeIter Iter;
	BTint value, found = 0;
	strcpy(nextword, word);
	gtk_list_store_clear(GTK_LIST_STORE(list));
	if(bfndky(dictionary, word, &value) ==  0){
		gtk_list_store_append(list, &Iter);
		gtk_list_store_set(list, &Iter, 0, nextword, -1);
		found = 1;
	}
	else
		btins(dictionary, nextword, "", 1);
	max = 10;
	while(bnxtky(dictionary, nextword, &value) == 0 && max){
		gtk_list_store_append(list, &Iter);
		gtk_list_store_set(list, &Iter, 0, nextword, -1);
		if(--max == 9) strcpy(tmpword, nextword);
	}
	if(!found) btdel(dictionary, word);
	if(Tab_pressed){
		if(strncmp(tmpword, word, strlen(word)) == 0){
			gtk_entry_set_text(GTK_ENTRY(entry), tmpword);
			gtk_editable_set_position(GTK_EDITABLE(entry), strlen(tmpword));
		}
	}
}

void delSuggest(GtkWidget *entry, GdkEvent *event){// gioi han ky tu, chi nhan alphabelt va tab
	GdkEventKey *keyEvent = (GdkEventKey*)event;
	char word[50];
	int len;
	strcpy(word, gtk_entry_get_text(GTK_ENTRY(entry)));
	if(keyEvent->keyval == GDK_KEY_Tab) suggestDel(word, TRUE);
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
		suggestDel(word, FALSE);
	}
}

void del(GtkWidget *w, gpointer data){
	GtkWidget *entry1= ((GtkWidget**)data)[0];
	GtkWidget *window1=((GtkWidget**)data)[1];

	a = gtk_entry_get_text(GTK_ENTRY(entry1));
	char mean[10000], word[50];
	int size;
	BTint x;
	strcpy(word,a);
	if (word[0] == '\0')
		Message(GTK_WIDGET(window1), GTK_MESSAGE_WARNING, "Warning!", "No part is left blank.");
	else if(bfndky(dictionary, word, &x) != 0)
		Message(GTK_WIDGET(window1), GTK_MESSAGE_ERROR, "Error!", "Word not found!");
	else
	if(btsel(dictionary,word,mean,100000,&size)==0){
		btdel(dictionary,word);
		Message(GTK_WIDGET(window1),GTK_MESSAGE_INFO, "Success!","Done!");
	}
	else
		Message(GTK_WIDGET(window1),GTK_MESSAGE_ERROR, "Error!","Can not delete!");
	gtk_window_close(GTK_WINDOW(window2));
}

void cfdel(GtkWidget *w, gpointer data){
	GtkWidget *fixed;
	GtkWidget *button1, *button2, *label;
	
	window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window2), "");
	gtk_window_set_default_size(GTK_WINDOW(window2), 200, 100);
	gtk_window_set_position(GTK_WINDOW(window2), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window2), FALSE);

	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window2), fixed);

	label = gtk_label_new("Are you sure?");
	gtk_fixed_put(GTK_FIXED(fixed), label, 60, 20);

	button1 = gtk_button_new_with_label("Yes");
	gtk_fixed_put(GTK_FIXED(fixed), button1, 30, 50);
	gtk_widget_set_size_request(button1, 60, 30);

	button2 = gtk_button_new_with_label("No");
	gtk_fixed_put(GTK_FIXED(fixed), button2, 110, 50);
	gtk_widget_set_size_request(button2, 60, 30);

	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(del), data);
	g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(close_window), window2);

	gtk_widget_show_all(window2);
}

void deleteWord(GtkWidget widget, gpointer window){
	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window1), "Delete word");
	gtk_window_set_default_size(GTK_WINDOW(window1), 546, 399);
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window1), FALSE);

	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window1), fixed);

	if(theme == 1){
		image = gtk_image_new_from_file("../Img/kaori4.jpg");
		gtk_widget_set_name(image, "imgDel");
	}
	if(theme == 2){
		image = gtk_image_new_from_file("../Img/tfwb7.jpg");
		gtk_widget_set_name(image, "imgDel");
	}
	gtk_container_add(GTK_CONTAINER(fixed), image);

	label = gtk_label_new("Input:");
	gtk_fixed_put(GTK_FIXED(fixed), label, 30, 30);

	entry = gtk_entry_new();
	if(theme == 1) gtk_widget_set_name(entry, "entry");
	if(theme == 2) gtk_widget_set_name(entry, "entry");
	gtk_fixed_put(GTK_FIXED(fixed), entry, 100, 25);
	gtk_widget_set_size_request(entry, 200, 30);
	gtk_entry_set_max_length(GTK_ENTRY(entry),50);
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Enter word here");

	GtkEntryCompletion *comple = gtk_entry_completion_new();
	gtk_entry_completion_set_text_column(comple, 0);
	list = gtk_list_store_new(1, G_TYPE_STRING);
	gtk_entry_completion_set_model(comple, GTK_TREE_MODEL(list));
	gtk_entry_set_completion(GTK_ENTRY(entry), comple);

	button1 = gtk_button_new_with_label("Delete");
	if(theme == 1) gtk_widget_set_name(button1, "buttonDel");
	if(theme == 2) gtk_widget_set_name(button1, "buttonDel");
	gtk_fixed_put(GTK_FIXED(fixed), button1, 350, 15);
	gtk_widget_set_size_request(button1, 80, 30);

	GtkWidget *data[2];
	data[0]= entry;
	data[1]= window1;

	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(cfdel), data);
	g_signal_connect(G_OBJECT(entry), "activate", G_CALLBACK(cfdel), data);
	g_signal_connect(entry, "key-press-event", G_CALLBACK(delSuggest), NULL);

	button2 = gtk_button_new_with_label("Back");
	gtk_widget_set_name(button2, "buttonDel");
	gtk_fixed_put(GTK_FIXED(fixed), button2, 450, 15);
	gtk_widget_set_size_request(button2, 80, 30);

	g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(close_window), window1);
	g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window1);

	gtk_main();
	return;
}