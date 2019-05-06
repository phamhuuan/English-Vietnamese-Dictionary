void add(GtkWidget *w, gpointer data);
void addWord(GtkWidget widget, gpointer window);

void add(GtkWidget *w, gpointer data){
	GtkTextBuffer *buffer1,*buffer2;
	GtkTextIter start, end,iter;
	char mean[10000], word[50];
	buffer1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GTK_TEXT_VIEW(view1)));
	gtk_text_buffer_get_iter_at_offset(buffer1, &iter, 0);

	gtk_text_buffer_insert(buffer1, &iter, "", -1);
	gtk_text_buffer_get_bounds (buffer1, &start, &end);
	b = gtk_text_buffer_get_text (buffer1, &start, &end, FALSE);

	strcpy(word,b);

	buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GTK_TEXT_VIEW(view2)));
	gtk_text_buffer_get_iter_at_offset(buffer2, &iter, 0);

	gtk_text_buffer_insert(buffer2, &iter, "", -1);
	gtk_text_buffer_get_bounds (buffer2, &start, &end);
	b = gtk_text_buffer_get_text (buffer2, &start, &end, FALSE);

	strcpy(mean,b);
	printf("\n");

	BTint x;

	if(word[0] == '\0' || mean[0] == '\0')
		Message(GTK_WIDGET(data), GTK_MESSAGE_WARNING, "Warning!", "No part is left blank!");
	else if(bfndky(dictionary, word, &x) == 0)
		Message(GTK_WIDGET(data), GTK_MESSAGE_ERROR, "Error!", "Word already in dictionary!");
	else{
		if(btins(dictionary,word, mean,10000))
			Message(GTK_WIDGET(data),GTK_MESSAGE_ERROR, "Error!","Can not add word!");
		else
			Message(GTK_WIDGET(data),GTK_MESSAGE_INFO, "Success!","Done!");
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
	gtk_widget_set_name(window1, "window2");

	label1 = gtk_label_new("Word:");
	gtk_fixed_put(GTK_FIXED(fixed), label1, 30, 30);

	view1 = gtk_text_view_new();
	gtk_widget_set_size_request(view1, 300, 30);
	gtk_fixed_put(GTK_FIXED(fixed), view1, 100, 25);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(view1), GTK_WRAP_WORD);
	gtk_widget_set_name(view1, "view1");

	label2 = gtk_label_new("Meaning:");
	gtk_fixed_put(GTK_FIXED(fixed), label2, 30, 200);

	GtkWidget *scrolling = gtk_scrolled_window_new(NULL, NULL);
	gtk_fixed_put(GTK_FIXED(fixed), scrolling, 100, 100);
	gtk_widget_set_size_request(scrolling, 300, 300);

	view2 = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scrolling), view2);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(view2), GTK_WRAP_WORD);
	gtk_widget_set_name(view2, "view2");

	button1 = gtk_button_new_with_label("Add");
	gtk_widget_set_name(button1, "buttonAdd");
	gtk_fixed_put(GTK_FIXED(fixed), button1, 450, 15);
	gtk_widget_set_size_request(button1, 90, 30);

	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(add), NULL);

	button2 = gtk_button_new_with_label("Back");
	gtk_widget_set_name(button2, "buttonAddBack");
	gtk_fixed_put(GTK_FIXED(fixed), button2, 560, 15);
	gtk_widget_set_size_request(button2, 90, 30);

	g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(close_window), window1);
	g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	image = gtk_image_new_from_file("../Img/kousei.jpg");
	gtk_fixed_put(GTK_FIXED(fixed), image, 450, 80);

	gtk_widget_show_all(window1);

	gtk_main();

	return;
}