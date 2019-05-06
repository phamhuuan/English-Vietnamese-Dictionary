void onOffMusic();
void changeVolume(GtkWidget *w, gpointer data);
void setting(GtkWidget widget, gpointer window);

GtkWidget *button1;
GtkWidget *textViewVolume;
int mute;
float vol;


void onOffMusic(){
    GtkWidget *image1;
    fileSettingMusic = fopen("../data/settingMusic.dat", "rb");
    fread(&s, sizeof(s), 1, fileSettingMusic);
    fclose(fileSettingMusic);
	if(s.mute == 1){
		al_set_sample_instance_gain(instance, s.vol);
        image1 = gtk_image_new_from_file("../Img/unmute.png");
        gtk_widget_set_tooltip_text(button1, "Click here to mute");
        gtk_button_set_image(GTK_BUTTON(button1), image1);
        s.mute = 0;
	}
	else{
		al_set_sample_instance_gain(instance, 0.0);
        image1 = gtk_image_new_from_file("../Img/mute.png");
        gtk_widget_set_tooltip_text(button1, "Click here to unmute");
        gtk_button_set_image(GTK_BUTTON(button1), image1);
		s.mute = 1;
	}
    fileSettingMusic = fopen("../data/settingMusic.dat", "wb");
    fwrite(&s, sizeof(s), 1, fileSettingMusic);
    fclose(fileSettingMusic);
}

void changeVolume(GtkWidget *w, gpointer data){
    // GtkWidget *textViewVolume = ((GtkWidget**)data)[0];
    GtkTextIter start, end, iter;
    GtkTextBuffer *buffer;
    char str[100];

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textViewVolume));
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

	gtk_text_buffer_insert(buffer, &iter, "", -1);
	gtk_text_buffer_get_bounds (buffer, &start, &end);
	b = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
    strcpy(str, b);
    s.vol = (float)atoi(str) / 100;
    fileSettingMusic = fopen("../data/settingMusic.dat", "wb");
    fwrite(&s, sizeof(s), 1, fileSettingMusic);
    fclose(fileSettingMusic);
    al_set_sample_instance_gain(instance, s.vol);
}

void setting(GtkWidget widget, gpointer window){
	GtkWidget *window1;
	GtkWidget *image1, *image2;
	GtkWidget *fixed;
    GtkWidget *button2;
    // GtkWidget *textViewVolume;
    char volText[80];

    fileSettingMusic = fopen("../data/settingMusic.dat", "rb");
    fread(&s, sizeof(s), 1, fileSettingMusic);
    fclose(fileSettingMusic);
    sprintf(volText, "%.0f", s.vol * 100);

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);//create a new GtkWindow
	gtk_window_set_title(GTK_WINDOW(window1), "Setting");//set the title of the GtkWindow
	gtk_window_set_default_size(GTK_WINDOW(window1), 300, 300);//set size of GtkWindow
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();//create new fixed
	gtk_container_add(GTK_CONTAINER(window1), fixed);

	button1 = gtk_button_new();
	if(s.mute == 1){
		image1 = gtk_image_new_from_file("../Img/mute.png");
		gtk_widget_set_tooltip_text(button1, "Click here to unmute");
	}
	else{
		image1 = gtk_image_new_from_file("../Img/unmute.png");
		gtk_widget_set_tooltip_text(button1, "Click here to mute");
	}
	gtk_button_set_image(GTK_BUTTON(button1), image1);
	gtk_widget_set_name(button1, "button2");
	gtk_fixed_put(GTK_FIXED(fixed), button1, 20, 20);
	gtk_widget_set_size_request(button1, 40, 40);

	g_signal_connect(button1, "clicked", G_CALLBACK(onOffMusic), NULL);

    button2 = gtk_button_new();
    image2 = gtk_image_new_from_file("../Img/settingVolume.png");
    gtk_button_set_image(GTK_BUTTON(button2), image2);
	gtk_widget_set_name(button2, "button2");
    gtk_fixed_put(GTK_FIXED(fixed), button2, 20, 100);
	gtk_widget_set_size_request(button2, 40, 40);

    textViewVolume = gtk_text_view_new();
    setTextView(volText, GTK_TEXT_VIEW(textViewVolume));
	gtk_widget_set_size_request(textViewVolume, 40, 40);
	gtk_fixed_put(GTK_FIXED(fixed), textViewVolume, 80, 100);
	gtk_widget_set_name(textViewVolume, "textViewVolume");

    // GtkWidget *data[1];
    // data[0] = textViewVolume;

    g_signal_connect(button2, "clicked", G_CALLBACK(changeVolume), NULL);

	gtk_widget_show_all(window1);
}