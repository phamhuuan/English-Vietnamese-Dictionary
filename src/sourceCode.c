long long j = 0;

void sourceCode();
void on_changed(GtkComboBox *widget, gpointer data);

void on_changed(GtkComboBox *widget, gpointer data){
    GtkComboBox *combo_box = widget;
    // GtkWidget *view = ((GtkWidget**)data)[0];

    gchar fileName[50];
    setTextView("", GTK_TEXT_VIEW(view));

    if(gtk_combo_box_get_active(combo_box) != 0){
        gchar *distro = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(combo_box));
        if(strcmp(distro, "README.md") == 0){
            strcpy(fileName, "../");
            strcat(fileName, distro);
        }
        else strcpy(fileName, distro);
        FILE *f = fopen(fileName, "r");
        char buffer[1000000], c;j = 0;
        while((c = getc(f)) != EOF){
            buffer[j++] = c;
        }buffer[j] = '\0';
        g_print("%lld\n", j);
        fclose(f);
        setTextView(buffer, GTK_TEXT_VIEW(view));
        g_free(distro);
    }
}

void sourceCode(){
    GtkWidget *window1, *fixed;
    GtkWidget *scrolling;
    GtkWidget *combo_box, *linkButton;
    gint i;

    window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window1), "Source code");
	gtk_window_set_default_size(GTK_WINDOW(window1), 600, 600);
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window1), FALSE);

    fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window1), fixed);

    combo_box = gtk_combo_box_text_new();
    gtk_fixed_put(GTK_FIXED(fixed), combo_box, 50, 20);
    const char *distros[] = {"Choose file", "README.md", "add.c", "closeWindow.c", "copyFile.c", "delete.c", "history.c", "init.c", "library.c", "main.c", "message.c", "myCSS.c", "mystyle.css", "restore.c", "search.c", "setTextView.c", "setting.c", "sourceCode.c", "team.c", "toturial.c"};

    for(i = 0; i < G_N_ELEMENTS(distros); i++){
  	    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), distros[i]);
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box), 0);

    scrolling = gtk_scrolled_window_new(NULL, NULL);
	gtk_fixed_put(GTK_FIXED(fixed), scrolling, 50, 80);
	gtk_widget_set_size_request(scrolling, 500, 500);

    view = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scrolling), view);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);

    FILE *f;
    f = fopen("../README.md", "r");
    gchar buffer[1000000], c;
    gint j = 0;
    while((c = getc(f)) != EOF){
        buffer[j++] = c;
    }buffer[j] = '\0';
    fclose(f);
    setTextView(buffer, GTK_TEXT_VIEW(view));

    g_signal_connect(combo_box, "changed", G_CALLBACK(on_changed), NULL);
    
    linkButton = gtk_link_button_new("Download");
  	gtk_link_button_set_uri(GTK_LINK_BUTTON(linkButton), "https://github.com/phamhuuan/English-Vietnamese-Dictionary.git");
	gtk_fixed_put(GTK_FIXED(fixed), linkButton, 400, 30);//toa do
	gtk_widget_set_size_request(linkButton, 110, 50);

    gtk_widget_show_all(window1);
}