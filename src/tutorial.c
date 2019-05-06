void sourceTutorial();
void searchTutorial();
void addTutorial();
void editTutorial();
void deleteTutorial();
void teamTutorial();
void libraryTutorial();
void remainTutorial();
void initMainTutorial();
void tutorial(GtkWidget widget, gpointer window);

GtkWidget *tutorialWindow, *tutorialFixed;
GtkWidget *tutorialLabel1;
GtkWidget *tutorialButton1, *tutorialButton2, *tutorialButton3, *tutorialButton4, *tutorialButton5, *tutorialButton6, *tutorialButton7;
GtkWidget *textView1, *textView2, *textView3;
GtkTextBuffer *buffer1, *buffer2, *buffer3;
GtkWidget *tutorialImage1;
GtkWidget *image1, *image2, *image3, *image4, *image5, *image6;


// void sourceTutorial(){
// 	const gchar *info = "- <a href=\"https://github.com\">Github</a>\n- <a href=\"http://stackoverflow.com\">Stackoverflow</a>\n- <a href=\"https://developer.gnome.org/gtk3/\">GTK 3.0+ documentation</a>\n- <a href=\"https://www.allegro.cc/manual/5/\">Allegro 5 documentation</a>";

// 	// window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);//create a new GtkWindow
// 	// gtk_window_set_title(GTK_WINDOW(window1), "Source");//set the title of the GtkWindow
// 	// gtk_window_set_default_size(GTK_WINDOW(window1), 220, 308);//set size of GtkWindow
// 	// gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

// 	// image = gtk_image_new_from_file("../Img/kaori2.jpg");//them anh tu file
// 	// gtk_container_add(GTK_CONTAINER(fixed), image);

// 	xlabel = 200, ylabel = 150;gtk_fixed_move(GTK_FIXED(fixed), label, xlabel, ylabel);
// 	gtk_label_set_markup(GTK_LABEL(label), info);	

// 	// gtk_widget_show_all(window1);
// }

void searchTutorial(){
    gtk_window_resize(GTK_WINDOW(tutorialWindow), 400, 600);

    initMainTutorial();

    gtk_image_set_from_file(GTK_IMAGE(tutorialImage1) ,"../Img/kaori7.jpg");

    gtk_fixed_move(GTK_FIXED(tutorialFixed), tutorialLabel1, 70, 100);
    gtk_label_set_markup(GTK_LABEL(tutorialLabel1), "Search tutorial");

    gtk_text_buffer_set_text(buffer1, "Step 1: Enter word into search blank.", -1);
    gtk_widget_set_size_request(textView1, 360, 30);
    gtk_fixed_move(GTK_FIXED(tutorialFixed), textView1, 20, 140);

    gtk_text_buffer_set_text(buffer2, "Step 2: Press search button.", -1);
    gtk_widget_set_size_request(textView2, 360, 30);
    gtk_fixed_move(GTK_FIXED(tutorialFixed), textView2, 20, 170);
}

void editTutorial(){
    gtk_window_resize(GTK_WINDOW(tutorialWindow), 400, 600);

    initMainTutorial();

    gtk_image_set_from_file(GTK_IMAGE(tutorialImage1), "../Img/kaori8.jpg");

    gtk_fixed_move(GTK_FIXED(tutorialFixed), tutorialLabel1, 85, 100);
    gtk_label_set_markup(GTK_LABEL(tutorialLabel1), "Edit tutorial");

    gtk_text_buffer_set_text(buffer1, "Step 1: Click on meaning blank.", -1);
    gtk_widget_set_size_request(textView1, 360, 30);
    gtk_fixed_move(GTK_FIXED(tutorialFixed), textView1, 20, 140);

    gtk_text_buffer_set_text(buffer2, "Step 2: Edit meaning at meaning blank.", -1);
    gtk_widget_set_size_request(textView2, 360, 30);
    gtk_fixed_move(GTK_FIXED(tutorialFixed), textView2, 20, 170);

    gtk_text_buffer_set_text(buffer3, "Step 3: Press \"Update meaning\" button to finish.", -1);
    gtk_widget_set_size_request(textView3, 360, 60);
    gtk_fixed_move(GTK_FIXED(tutorialFixed), textView3, 20, 200);
}

void addTutorial(){
    gtk_window_resize(GTK_WINDOW(tutorialWindow), 400, 600);

    initMainTutorial();

    gtk_image_set_from_file(GTK_IMAGE(tutorialImage1), "../Img/kaori10.jpg");

    gtk_fixed_move(GTK_FIXED(tutorialFixed), tutorialLabel1, 90, 100);
    gtk_label_set_markup(GTK_LABEL(tutorialLabel1), "Add tutorial");

    gtk_text_buffer_set_text(buffer1, "Step 1: Enter word into input blank and meaning blank.", -1);
    gtk_widget_set_size_request(textView1, 360, 60);
    gtk_fixed_move(GTK_FIXED(tutorialFixed), textView1, 20, 140);

    gtk_text_buffer_set_text(buffer2, "Step 2: Press \"Add\" button to finish.", -1);
    gtk_widget_set_size_request(textView2, 360, 30);
    gtk_fixed_move(GTK_FIXED(tutorialFixed), textView2, 20, 190);
}

void deleteTutorial(){
    gtk_window_resize(GTK_WINDOW(tutorialWindow), 400, 600);

    initMainTutorial();

    gtk_image_set_from_file(GTK_IMAGE(tutorialImage1), "../Img/kaori11.jpg");

    gtk_fixed_move(GTK_FIXED(tutorialFixed), tutorialLabel1, 70, 100);
    gtk_label_set_markup(GTK_LABEL(tutorialLabel1), "Delete tutorial");

    gtk_text_buffer_set_text(buffer1, "Step 1: Enter word into input blank.", -1);
    gtk_widget_set_size_request(textView1, 360, 60);
    gtk_fixed_move(GTK_FIXED(tutorialFixed), textView1, 20, 140);

    gtk_text_buffer_set_text(buffer2, "Step 2: Press \"Delete\" button to finish.", -1);
    gtk_widget_set_size_request(textView2, 360, 30);
    gtk_fixed_move(GTK_FIXED(tutorialFixed), textView2, 20, 170);
}

void libraryTutorial(){
    gtk_window_resize(GTK_WINDOW(tutorialWindow), 400, 600);

    initMainTutorial();

    gtk_image_set_from_file(GTK_IMAGE(tutorialImage1), "../Img/kaori12.jpg");

    gtk_fixed_move(GTK_FIXED(tutorialFixed), tutorialLabel1, 85, 100);
    gtk_label_set_markup(GTK_LABEL(tutorialLabel1), "Library tutorial");

    gtk_text_buffer_set_text(buffer1, "Add: At \"Search\" window press \"Add to library\" button.", -1);
    gtk_widget_set_size_request(textView1, 360, 50);
    gtk_fixed_move(GTK_FIXED(tutorialFixed), textView1, 20, 140);

    gtk_text_buffer_set_text(buffer2, "Remove: At \"Search\" window press \"Remove from library\" button.", -1);
    gtk_widget_set_size_request(textView2, 360, 50);
    gtk_fixed_move(GTK_FIXED(tutorialFixed), textView2, 20, 190);

    gtk_text_buffer_set_text(buffer3, "Remove all: At \"Library\" window press \"Remove all\" button.", -1);
    gtk_widget_set_size_request(textView3, 360, 50);
    gtk_fixed_move(GTK_FIXED(tutorialFixed), textView3, 20, 240);
}

void remainTutorial(){
    gtk_window_resize(GTK_WINDOW(tutorialWindow), 400, 600);
    gtk_image_set_from_file(GTK_IMAGE(tutorialImage1), "../Img/kaori9.jpg");

    initMainTutorial();

    gtk_fixed_move(GTK_FIXED(tutorialFixed), tutorialLabel1, 130, 100);
    gtk_label_set_markup(GTK_LABEL(tutorialLabel1), "Tutorial");
}

void initMainTutorial(){
    gtk_fixed_move(GTK_FIXED(tutorialFixed), tutorialLabel1, 0, 0);
    gtk_label_set_markup(GTK_LABEL(tutorialLabel1), "");

	gtk_widget_set_size_request(textView1, 0, 0);
    gtk_fixed_move(GTK_FIXED(tutorialFixed), textView1, 0, 0);
    gtk_text_buffer_set_text(buffer1, "", -1);

    gtk_widget_set_size_request(textView2, 0, 0);
    gtk_fixed_move(GTK_FIXED(tutorialFixed), textView2, 0, 0);
    gtk_text_buffer_set_text(buffer2, "", -1);

    gtk_widget_set_size_request(textView3, 0, 0);
    gtk_fixed_move(GTK_FIXED(tutorialFixed), textView3, 0, 0);
    gtk_text_buffer_set_text(buffer3, "", -1);
}

void tutorial(GtkWidget widget, gpointer window){
	tutorialWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);//create a new GtkWindow
	gtk_window_set_title(GTK_WINDOW(tutorialWindow), "Tutorial");//set the title of the GtkWindow
	gtk_window_set_default_size(GTK_WINDOW(tutorialWindow), 400, 600);//set size of GtkWindow
	gtk_window_set_position(GTK_WINDOW(tutorialWindow), GTK_WIN_POS_CENTER);

	tutorialFixed = gtk_fixed_new();//create new fixed
	gtk_container_add(GTK_CONTAINER(tutorialWindow), tutorialFixed);//add widget to container
    
	tutorialImage1 = gtk_image_new_from_file("../Img/kaori9.jpg");//them anh tu file
	gtk_container_add(GTK_CONTAINER(tutorialFixed), tutorialImage1);
	gtk_widget_set_name(tutorialImage1, "imageTutorial");

    tutorialLabel1 = gtk_label_new("Tutorial");
	gtk_widget_set_name(tutorialLabel1, "labelTitleSearchTutorial");
	gtk_fixed_put(GTK_FIXED(tutorialFixed), tutorialLabel1, 130, 100);

    buffer1 = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(buffer1, "", -1);
	textView1 = gtk_text_view_new_with_buffer(buffer1);
	gtk_widget_set_name(textView1, "textViewSearchTutorial");
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textView1), FALSE);
    gtk_fixed_put(GTK_FIXED(tutorialFixed), textView1, 0, 0);

    buffer2 = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(buffer2, "", -1);
	textView2 = gtk_text_view_new_with_buffer(buffer2);
	gtk_widget_set_name(textView2, "textViewSearchTutorial");
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textView2), FALSE);
    gtk_fixed_put(GTK_FIXED(tutorialFixed), textView2, 0, 0);

    buffer3 = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(buffer3, "", -1);
	textView3 = gtk_text_view_new_with_buffer(buffer3);
	gtk_widget_set_name(textView3, "textViewSearchTutorial");
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textView3), FALSE);
    gtk_fixed_put(GTK_FIXED(tutorialFixed), textView3, 0, 0);
    
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textView1), GTK_WRAP_WORD);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textView2), GTK_WRAP_WORD);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textView3), GTK_WRAP_WORD);

	image1 = gtk_image_new_from_file("../Img/searchButton60x60.png");
	tutorialButton1 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(tutorialButton1), image1);
	gtk_fixed_put(GTK_FIXED(tutorialFixed), tutorialButton1, 0, 0);
	gtk_widget_set_name(tutorialButton1, "buttonTutorial");
	gtk_widget_set_size_request(tutorialButton1, 80, 80);
	gtk_widget_set_tooltip_text(tutorialButton1, "Search");
	
	image2 = gtk_image_new_from_file("../Img/editButton60x60.png");
	tutorialButton2 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(tutorialButton2), image2);
	gtk_fixed_put(GTK_FIXED(tutorialFixed), tutorialButton2, 80, 0);
	gtk_widget_set_name(tutorialButton2, "buttonTutorial");
	gtk_widget_set_size_request(tutorialButton2, 80, 80);
	gtk_widget_set_tooltip_text(tutorialButton2, "Edit");

    image3 = gtk_image_new_from_file("../Img/addButton60x60.png");
	tutorialButton3 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(tutorialButton3), image3);
	gtk_fixed_put(GTK_FIXED(tutorialFixed), tutorialButton3, 160, 0);
	gtk_widget_set_name(tutorialButton3, "buttonTutorial");
	gtk_widget_set_size_request(tutorialButton3, 80, 80);
	gtk_widget_set_tooltip_text(tutorialButton3, "Add");

    image4 = gtk_image_new_from_file("../Img/deleteButton60x60.png");
	tutorialButton4 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(tutorialButton4), image4);
	gtk_fixed_put(GTK_FIXED(tutorialFixed), tutorialButton4, 240, 0);
	gtk_widget_set_name(tutorialButton4, "buttonTutorial");
	gtk_widget_set_size_request(tutorialButton4, 80, 80);
	gtk_widget_set_tooltip_text(tutorialButton4, "Delete");

    image5 = gtk_image_new_from_file("../Img/libraryButton60x60.png");
	tutorialButton5 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(tutorialButton5), image5);
	gtk_fixed_put(GTK_FIXED(tutorialFixed), tutorialButton5, 320, 0);
	gtk_widget_set_name(tutorialButton5, "buttonTutorial");
	gtk_widget_set_size_request(tutorialButton5, 80, 80);
	gtk_widget_set_tooltip_text(tutorialButton5, "Library");

    tutorialButton6 = gtk_button_new_with_label("Back");
	gtk_fixed_put(GTK_FIXED(tutorialFixed), tutorialButton6, 120, 550);
    gtk_widget_set_name(tutorialButton6, "buttonTutorial");
	gtk_widget_set_size_request(tutorialButton6, 80, 40);
	gtk_widget_set_tooltip_text(tutorialButton6, "Back");

    tutorialButton7 = gtk_button_new_with_label("Exit");
	gtk_fixed_put(GTK_FIXED(tutorialFixed), tutorialButton7, 200, 550);
    gtk_widget_set_name(tutorialButton7, "buttonTutorial");
	gtk_widget_set_size_request(tutorialButton7, 80, 40);
	gtk_widget_set_tooltip_text(tutorialButton7, "Exit");

	g_signal_connect(G_OBJECT(tutorialButton1), "clicked", G_CALLBACK(searchTutorial), NULL);
	g_signal_connect(G_OBJECT(tutorialButton2), "clicked", G_CALLBACK(editTutorial), NULL);
	g_signal_connect(G_OBJECT(tutorialButton3), "clicked", G_CALLBACK(addTutorial), NULL);
	g_signal_connect(G_OBJECT(tutorialButton4), "clicked", G_CALLBACK(deleteTutorial), NULL);
	g_signal_connect(G_OBJECT(tutorialButton5), "clicked", G_CALLBACK(libraryTutorial), NULL);
    g_signal_connect(G_OBJECT(tutorialButton6), "clicked", G_CALLBACK(remainTutorial), NULL);
    g_signal_connect(G_OBJECT(tutorialButton7), "clicked", G_CALLBACK(close_window), tutorialWindow);

	gtk_widget_show_all(tutorialWindow);
}