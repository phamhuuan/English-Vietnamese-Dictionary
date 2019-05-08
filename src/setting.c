void onOffMusic();
void changeVolume(GtkRange *range, gpointer data);
void setting(GtkWidget widget, gpointer window);
void changeTheme();

GtkWidget *button1, *label1;
GtkWidget *textViewVolume;

GtkWidget *spinButton1;
GtkAdjustment *adjustment;
GtkAdjustment *hadjustment;
GtkWidget *hScale;

void onOffMusic(){
    GtkWidget *image1;
    fileSettingMusic = fopen("../data/settingMusic.dat", "rb");
    fscanf(fileSettingMusic, "%d %f", &s.mute, &s.vol);
    fclose(fileSettingMusic);
	if(s.mute == 1){//dang mute --> k mute
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
    fprintf(fileSettingMusic, "%d %f", s.mute, s.vol);
    fclose(fileSettingMusic);
}

void changeVolume(GtkRange *range, gpointer data){
    gdouble pos = gtk_range_get_value(range);
    s.vol = pos / 100;
    if(s.mute == 1){
        s.mute = 0;
        image1 = gtk_image_new_from_file("../Img/unmute.png");
        gtk_widget_set_tooltip_text(button1, "Click here to mute");
        gtk_button_set_image(GTK_BUTTON(button1), image1);
    }
    fileSettingMusic = fopen("../data/settingMusic.dat", "wb");
    fprintf(fileSettingMusic, "%d %f", s.mute, s.vol);
    fclose(fileSettingMusic);
    al_set_sample_instance_gain(instance, s.vol);
    gchar *str = g_strdup_printf("Volume %.0f", pos);
    gtk_label_set_text(GTK_LABEL(label1), str);
}

void changeTheme(){
    theme = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(spinButton1));
    fileSettingTheme = fopen("../data/settingTheme.dat", "wb");
    fprintf(fileSettingTheme, "%d", theme);
    fclose(fileSettingTheme);
    if(theme == 1){
        gtk_image_set_from_file(GTK_IMAGE(image), "../Img/shigatsuwakiminouso2.jpg");
        al_destroy_sample_instance(instance);
        sample = al_load_sample("../Img/Orange7.wav");
        instance = al_create_sample_instance(sample);
        al_attach_sample_instance_to_mixer(instance, al_get_default_mixer());
        al_set_sample_instance_playing(instance, true);
        al_set_sample_instance_playmode(instance, ALLEGRO_PLAYMODE_LOOP);
    }
    if(theme == 2){
        gtk_image_set_from_file(GTK_IMAGE(image), "../Img/tfwb1.jpg");
        al_destroy_sample_instance(instance);
        sample = al_load_sample("../Img/GotoubunNoKimochi.wav");
        instance = al_create_sample_instance(sample);
        al_attach_sample_instance_to_mixer(instance, al_get_default_mixer());
        al_set_sample_instance_playing(instance, true);
        al_set_sample_instance_playmode(instance, ALLEGRO_PLAYMODE_LOOP);
    }
}

void setting(GtkWidget widget, gpointer window){
	GtkWidget *window1;
	GtkWidget *image1, *image2, *image3;
	GtkWidget *fixed;
    GtkWidget *button2, *button3;
    // image = gtk_image_new_from_file("../Img/tfwb1.jpg");
    fileSettingMusic = fopen("../data/settingMusic.dat", "rb");
    fscanf(fileSettingMusic, "%d %f", &s.mute, &s.vol);
    fclose(fileSettingMusic);

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
    gtk_fixed_put(GTK_FIXED(fixed), button2, 20, 80);
	gtk_widget_set_size_request(button2, 40, 40);

    hadjustment = gtk_adjustment_new (s.vol * 100, 0, 100, 1, 0, 0);
    hScale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, hadjustment);
    gtk_scale_set_digits (GTK_SCALE(hScale), 0);
    gtk_widget_set_hexpand(hScale, TRUE);
    gtk_widget_set_valign(hScale, GTK_ALIGN_START);
    gtk_widget_set_name(hScale, "hScale");
    gtk_fixed_put(GTK_FIXED(fixed), hScale, 80, 80);

    label1 = gtk_label_new("");
    gchar *str = g_strdup_printf("Volume: %.0f", s.vol * 100);
    gtk_label_set_text(GTK_LABEL(label1), str);
    gtk_fixed_put(GTK_FIXED(fixed), label1, 140, 105);

    button3 = gtk_button_new();
    image3 = gtk_image_new_from_file("../Img/settingTheme.png");
    gtk_button_set_image(GTK_BUTTON(button3), image3);
	gtk_widget_set_name(button3, "button2");
    gtk_fixed_put(GTK_FIXED(fixed), button3, 20, 140);
	gtk_widget_set_size_request(button3, 40, 40);

    fileSettingTheme = fopen("../data/settingTheme.dat", "rb");
    fscanf(fileSettingTheme, "%d", &theme);
    fclose(fileSettingTheme);

    adjustment = gtk_adjustment_new(theme, 1, 2, 1, 0, 0);//khoi tao - start - end - step - page_increment - page_size
    spinButton1 = gtk_spin_button_new(adjustment, 1, 0);
    gtk_widget_set_name(spinButton1, "spinButton1");
    gtk_fixed_put(GTK_FIXED(fixed), spinButton1, 80, 150);

    g_signal_connect(hScale, "value-changed", G_CALLBACK(changeVolume), NULL);
    g_signal_connect(spinButton1, "value-changed", G_CALLBACK(changeTheme), NULL);

	gtk_widget_show_all(window1);
}