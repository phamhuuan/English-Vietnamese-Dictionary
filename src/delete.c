void del(GtkWidget *w, gpointer data);
void deleteWord(GtkWidget widget, gpointer window);

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
	else if (bfndky(dictionary, word, &x ) != 0)
		Message(GTK_WIDGET(window1), GTK_MESSAGE_ERROR, "Error!", "Word not found!");
	else
	if(btsel(dictionary,word,mean,100000,&size)==0){
		btdel(dictionary,word);
		Message(GTK_WIDGET(window1),GTK_MESSAGE_INFO, "Success!","Done!");
	}
	else
		Message(GTK_WIDGET(window1),GTK_MESSAGE_ERROR, "Error!","Can not delete!");
	return;
}

void deleteWord(GtkWidget widget, gpointer window){
	GtkWidget *fixed, *image;
	GtkWidget *button1,*window1,*label,*entry,*button2;

	myCSS();

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window1), "Delete word");
	gtk_window_set_default_size(GTK_WINDOW(window1), 546, 399);
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window1), fixed);

	image = gtk_image_new_from_file("../Img/kaori4.jpg");
	gtk_widget_set_name(image, "imgDel");
	gtk_container_add(GTK_CONTAINER(fixed), image);

	label = gtk_label_new("Input:");
	gtk_fixed_put(GTK_FIXED(fixed), label, 30, 30);

	entry = gtk_entry_new();
	gtk_widget_set_name(entry, "entry");
	gtk_fixed_put(GTK_FIXED(fixed), entry, 100, 25);
	gtk_widget_set_size_request(entry, 200, 30);
	gtk_entry_set_max_length(GTK_ENTRY(entry),100);

	button1 = gtk_button_new_with_label("Delete");
	gtk_widget_set_name(button1, "buttonDel");
	gtk_fixed_put(GTK_FIXED(fixed), button1, 350, 15);
	gtk_widget_set_size_request(button1, 80, 30);

	GtkWidget *data[2];
	data[0]= entry;
	data[1]= window1;

	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(del), data);
	g_signal_connect(G_OBJECT(entry), "activate", G_CALLBACK(del), data);

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