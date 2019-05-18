void add(GtkWidget *w, gpointer data);
void addWord(GtkWidget widget, gpointer window);

void add(GtkWidget *w, gpointer data){
	GtkWidget *entry1 = ((GtkWidget**)data)[0];
	GtkWidget *view1 = ((GtkWidget**)data)[1];
	GtkWidget *window1 = ((GtkWidget**)data)[2];

	GtkTextBuffer *buffer1;
	GtkTextIter start, end,iter;
	char mean[10000], word[50];
	a = gtk_entry_get_text(GTK_ENTRY(entry1));

	strcpy(word,a);

	buffer1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view1));
	gtk_text_buffer_get_iter_at_offset(buffer1, &iter, 0);

	gtk_text_buffer_insert(buffer1, &iter, "", -1);
	gtk_text_buffer_get_bounds (buffer1, &start, &end);
	b = gtk_text_buffer_get_text (buffer1, &start, &end, FALSE);

	strcpy(mean,b);

	BTint x;

	if(word[0] == '\0' || mean[0] == '\0')
		Message(GTK_WIDGET(window1), GTK_MESSAGE_WARNING, "Warning!", "No part is left blank!");
	else if(bfndky(dictionary, word, &x) == 0)
		Message(GTK_WIDGET(window1), GTK_MESSAGE_ERROR, "Error!", "Word already in dictionary!");
	else{
		if(btins(dictionary,word, mean,10000)!=0)
			Message(GTK_WIDGET(window1),GTK_MESSAGE_ERROR, "Error!","Can not add word!");
		else
			Message(GTK_WIDGET(window1),GTK_MESSAGE_INFO, "Success!","Done!");
	}
	return;
}

void addWord(GtkWidget widget, gpointer window){
	GtkWidget *fixed, *button2, *image;
	GtkWidget *button1,*window1,*label1,*label2;

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window1), "Add word");
	gtk_window_set_default_size(GTK_WINDOW(window1), 750, 450);
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

	myCSS();

	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window1), fixed);
	if(theme == 1) gtk_widget_set_name(window1, "window2");
	if(theme == 2) gtk_widget_set_name(window1, "window2theme2");

	label1 = gtk_label_new("Word:");
	gtk_fixed_put(GTK_FIXED(fixed), label1, 30, 30);

	entry_search = gtk_entry_new();
	gtk_widget_set_size_request(entry_search, 300, 30);
	gtk_fixed_put(GTK_FIXED(fixed), entry_search, 100, 25);
	gtk_entry_set_max_length(GTK_ENTRY(entry_search), 50);
	if(theme == 1) gtk_widget_set_name(entry_search, "view1");
	if(theme == 2) gtk_widget_set_name(entry_search, "view1theme2");
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry_search), "Enter word here");

	label2 = gtk_label_new("Meaning:");
	gtk_fixed_put(GTK_FIXED(fixed), label2, 30, 200);

	GtkWidget *scrolling = gtk_scrolled_window_new(NULL, NULL);
	gtk_fixed_put(GTK_FIXED(fixed), scrolling, 100, 100);
	gtk_widget_set_size_request(scrolling, 300, 300);

	view1 = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scrolling), view1);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(view1), GTK_WRAP_WORD);
	if(theme == 1) gtk_widget_set_name(view1, "view2");
	if(theme == 2) gtk_widget_set_name(view1, "view1theme2");

	button1 = gtk_button_new_with_label("Add");
	if(theme == 1) gtk_widget_set_name(button1, "buttonAdd");
	if(theme == 2) gtk_widget_set_name(button1, "buttonAddtheme2");
	gtk_fixed_put(GTK_FIXED(fixed), button1, 450, 15);
	gtk_widget_set_size_request(button1, 90, 30);

	button2 = gtk_button_new_with_label("Back");
	if(theme == 1) gtk_widget_set_name(button2, "buttonAddBack");
	if(theme == 2) gtk_widget_set_name(button2, "buttonAddtheme2");
	gtk_fixed_put(GTK_FIXED(fixed), button2, 560, 15);
	gtk_widget_set_size_request(button2, 90, 30);

	if(theme == 1) image = gtk_image_new_from_file("../Img/kousei.jpg");//them anh tu file
	if(theme == 2) image = gtk_image_new_from_file("../Img/tfwb3.jpg");
	gtk_fixed_put(GTK_FIXED(fixed), image, 450, 80);

	GtkWidget *data[3];
	data[0] = entry_search;
	data[1] = view1;
	data[2] = window1;

	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(add), data);
	g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(close_window), window1);
	g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window1);

	gtk_main();

	return;
}