void removeAll();
void library(GtkWidget widget, gpointer window);
void getLabel(GtkButton *button);
void initMainLibrary();
void none();
// char word[50];
GtkWidget *fixed, *fixed2, *scrolling;
GtkWidget *window1, *scrolling2[100], *button, *button2[100], /**fixed,*/ /**fixed2,*/ *fixed3, *label[100], *image;
char mean[100000];
int count = 0, size;
char* x = NULL;
char test[50];

void none(){}

void removeAll(){
	char word[50];
	char* x = NULL;
	int size;
    btsel(libraryTree, "", x, 1, &size);
    if(btseln(libraryTree, word, x, 0, &size) == 0) gtk_container_remove(GTK_CONTAINER(fixed), scrolling);
	btsel(libraryTree, "", x, 1, &size);
    while(btseln(libraryTree, word, x, 0, &size) == 0) bdelky(libraryTree, word);
}

void getLabel(GtkButton *button2){
    char word[50];
    strcpy(word, gtk_button_get_label(button2));
    strcpy(test, word);
    BTint x;
    bfndky(libraryTree, word, &x);
    bdelky(libraryTree, word);
    initMainLibrary();
}

void initMainLibrary(){
    char word[50];
    count = 0;
    btsel(libraryTree, "", NULL, 1, &size);
    while(btseln(libraryTree, word, NULL, 0, &size) == 0){
        btsel(dictionary, word, mean, 100000, &size);
        gtk_fixed_move(GTK_FIXED(fixed2), scrolling2[count], 0, 120*count);
        gtk_widget_set_size_request(scrolling2[count], 250, 100);
		gtk_label_set_text(GTK_LABEL(label[count]), mean);
        gtk_button_set_label(GTK_BUTTON(button2[count]), word);
        g_signal_connect(button2[count], "clicked", G_CALLBACK(getLabel), button2[count]);
        count++;
    }
    gtk_container_remove(GTK_CONTAINER(fixed2), scrolling2[count]);
    count = 0;
}

void library(GtkWidget widget, gpointer window){
    char word[50];
	myCSS();

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window1), "Library");
	gtk_window_set_default_size(GTK_WINDOW(window1), 600, 500);
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window1), fixed);

	image = gtk_image_new_from_file("../Img/tsubaki.jpg");//them anh tu file
	gtk_container_add(GTK_CONTAINER(fixed), image);

	button = gtk_button_new_with_label("Remove all");
	gtk_widget_set_name(button, "buttonRemoveAll");
	gtk_fixed_put(GTK_FIXED(fixed), button, 20, 20);
	gtk_widget_set_size_request(button, 80, 80);

	scrolling = gtk_scrolled_window_new(NULL, NULL);
	gtk_fixed_put(GTK_FIXED(fixed), scrolling, 350, 20);
	gtk_widget_set_size_request(scrolling, 250, 450);

	fixed2 = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(scrolling), fixed2);

    btsel(libraryTree, "", x, 1, &size);
    while(btseln(libraryTree, word, x, 0, &size) == 0){
        btsel(dictionary, word, mean, 100000, &size);
        scrolling2[count] = gtk_scrolled_window_new(NULL, NULL);
        gtk_widget_set_name(scrolling2[count], "scrolling");
        gtk_fixed_put(GTK_FIXED(fixed2), scrolling2[count], 0, 120*count);
        gtk_widget_set_size_request(scrolling2[count], 250, 100);
        fixed3 = gtk_fixed_new();
		gtk_container_add(GTK_CONTAINER(scrolling2[count]), fixed3);
		label[count] = gtk_label_new(mean);
		gtk_fixed_put(GTK_FIXED(fixed3), label[count], 0, 35);
        button2[count] = gtk_button_new();
        gtk_button_set_label(GTK_BUTTON(button2[count]) , word);
        gtk_fixed_put(GTK_FIXED(fixed3), button2[count], 0, 0);
        gtk_widget_set_size_request(button2[count], 250, 30);
        gtk_widget_set_name(button2[count], "buttonLibrary");
        g_signal_connect(button2[count], "clicked", G_CALLBACK(getLabel), button2[count]);
        count++;
    }
    count = 0;

	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(removeAll), NULL);
	gtk_widget_show_all(window1);
}