void phamhuuan(GtkWidget widget, gpointer window);
void doanngocchien(GtkWidget widget, gpointer window);
void team(GtkWidget widget, gpointer window);

void team(GtkWidget widget, gpointer window){
	GtkWidget *image1, *image2, *label1, *label2, *button1, *button2, *window1, *fixed, *image3;
	const gchar *info1 = "Phạm Hữu An\nContact me: <a href=\"https://www.facebook.com/supersmartpog\">Facebook</a>, <a href=\"mailto:phaman3899@gmail.com\">Gmail</a>";
	const gchar *info2 = "Đoàn Ngọc Chiến\nContact me: <a href=\"https://www.facebook.com/100004695601749\">Facebook</a>, <a href=\"mailto:chiendoanngoc1705@gmail.com\">Gmail</a>";

	myCSS();

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(window1, "window3");
	if(theme == 1) gtk_window_set_title(GTK_WINDOW(window1), "About team");
	if(theme == 2) gtk_window_set_title(GTK_WINDOW(window1), "About team");
	gtk_window_set_default_size(GTK_WINDOW(window1), 500, 240);
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window1), fixed);

	button1 = gtk_button_new();
	gtk_fixed_put(GTK_FIXED(fixed), button1, 20, 20);
	gtk_widget_set_size_request(button1, 80, 80);
	image1 = gtk_image_new_from_file("../Img/an.jpg");
	gtk_widget_set_tooltip_text(button1, "Click here see more");
	gtk_container_add(GTK_CONTAINER(button1), image1);
	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(phamhuuan), NULL);
	label1 = gtk_label_new(NULL);
	gtk_fixed_put(GTK_FIXED(fixed), label1, 120, 50);
	gtk_label_set_markup(GTK_LABEL(label1), info1);

	button2 = gtk_button_new();
	gtk_fixed_put(GTK_FIXED(fixed), button2, 20, 120);
	gtk_widget_set_size_request(button2, 80, 80);
	image2 = gtk_image_new_from_file("../Img/chien.jpg");
	gtk_widget_set_tooltip_text(button2, "Click here see more");
	gtk_container_add(GTK_CONTAINER(button2), image2);
	g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(doanngocchien), NULL);
	label2 = gtk_label_new(NULL);
	gtk_fixed_put(GTK_FIXED(fixed), label2, 120, 150);
	gtk_label_set_markup(GTK_LABEL(label2), info2);

	if(theme == 1) image3 = gtk_image_new_from_file("../Img/kaoriandkousei.jpg");//them anh tu file
	if(theme == 2) image3 = gtk_image_new_from_file("../Img/tfwb4.jpg");
	gtk_fixed_put(GTK_FIXED(fixed), image3, 350, 0);

	gtk_widget_show_all(window1);
}

void phamhuuan(GtkWidget widget, gpointer window){
	about_dialog = gtk_about_dialog_new();
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_dialog), "Phạm Hữu An");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog), "Mã số sinh viên: 20176676");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about_dialog), "Nhóm 74");
	gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(about_dialog), NULL);
	gtk_dialog_run(GTK_DIALOG(about_dialog));
	gtk_widget_destroy(about_dialog);
}

void doanngocchien(GtkWidget widget, gpointer window){
	about_dialog = gtk_about_dialog_new();
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_dialog), "Đoàn Ngọc Chiến");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog), "Mã số sinh viên: 20176701");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about_dialog), "Nhóm 74");
	gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(about_dialog), NULL);
	gtk_dialog_run(GTK_DIALOG(about_dialog));
	gtk_widget_destroy(about_dialog);
}