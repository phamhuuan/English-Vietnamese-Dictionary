// #include <gtk/gtk.h>
#include <gtk/gtk.h>
#include <stdio.h>																															
#include <stdlib.h>
#include <string.h>
#include "inc/btree.h"
#include "jrb.h"
#include <gdk/gdkkeysyms.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define WORD_MAX 255
#define MEAN_MAX 10000
//Khai bao
BTA* dictionary = NULL;
BTA *libraryTree = NULL;
const gchar *a, *b;

GtkWidget *textView, *view1, *view2, *about_dialog, *entry_search;
GtkWidget *window;
GtkListStore *list;
static char code[128] = {0};

void separate_mean(char* mean);
int convert_text_to_bt(char * filename);

void sourceTutorial();
void searchTutorial();
void addTutorial();
void editTutorial();
void deleteTutorial();
void teamTutorial();
void libraryTutorial();
void tutorial(GtkWidget widget, gpointer window);

void setTextView(char* text);//add word to caching
const char* soundex(const char *s);//soundex function
int prefix(const char *big, const char *small);
int btfind(char *word);
void Message(GtkWidget *parent, GtkMessageType type,  char *mms, char *content);
int commond_char(char * str1, char * str2, int start);
void jrb_to_list(JRB nextWordArray, int number);
int insert_insoundexlist(char *soundexlist , char *newword,  char *word, char *soundexWord);
static void search(GtkWidget *w, gpointer data);
void suggest(char * word, gboolean Tab_pressed);
gboolean search_suggest(GtkWidget * entry, GdkEvent * event, gpointer No_need);
static void edit(GtkWidget *w, gpointer data);
void addToLibrary(GtkWidget *w, gpointer data);
void removeFromLibrary(GtkWidget *w, gpointer data);
void close_window(GtkWidget *widget, gpointer window);
void searchWord(GtkWidget widget, gpointer window);

static void add(GtkWidget *w, gpointer data);
void addWord(GtkWidget widget, gpointer window);

static void del(GtkWidget *w, gpointer data);
void deleteWord(GtkWidget widget, gpointer window);

void restore();

void removeAll();
void library(GtkWidget widget, gpointer window);

void team(GtkWidget widget, gpointer window);

void myCSS(void);

int main(int argc, char *argv[]){
	btinit();
	dictionary = btopn("data/evdic.dat", 0, 1);//cho phep update va share
	if(dictionary == NULL){
		g_print("Waiting for creating data...\n");
		convert_text_to_bt("data/AnhViet.txt");
		dictionary = btopn("data/evdic.dat", 0, 1);
		g_print("Done!\n");
	}
	libraryTree = btopn("data/library.dat", 0, 1);
	// gtk_widget_set_name(window, "window");
	GtkWidget *image, *fixed;
	GtkWidget *button1, *button2, *button3, *button4, *button5, *button6, *button7, *button8;

	gtk_init(&argc, &argv);//khoi tao gtk

	/*Tao cua so*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//create a new GtkWindow
	gtk_window_set_title(GTK_WINDOW(window), "English-Vietnamese Dictionary");//set the title of the GtkWindow
	gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);//set size of GtkWindow
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);//Cua so se xuat hien o giua man hinh


	/*Tao hinh nen*/
	fixed = gtk_fixed_new();//create new fixed
	gtk_container_add(GTK_CONTAINER(window), fixed);//add widget to container
	image = gtk_image_new_from_file("Img/shigatsuwakiminouso2.jpg");//them anh tu file
	gtk_container_add(GTK_CONTAINER(fixed), image);

	myCSS();

	button1 = gtk_button_new_with_label("Tutorial");//tao nut
	gtk_widget_set_name(button1, "button1");//dung cho myCSS
	gtk_fixed_put(GTK_FIXED(fixed), button1, 350, 160);//toa do
	gtk_widget_set_size_request(button1, 240, 50);//size
	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(tutorial), NULL);

	button2 = gtk_button_new_with_label("Search word");
	gtk_widget_set_name(button2, "button2");
	gtk_fixed_put(GTK_FIXED(fixed), button2, 350, 220);
	gtk_widget_set_size_request(button2, 110, 50);
	gtk_widget_set_tooltip_text(button2, "Click to search a word");
	g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(searchWord), NULL);

	button3 = gtk_button_new_with_label("Add word");
	gtk_widget_set_name(button3, "button2");
	gtk_fixed_put(GTK_FIXED(fixed), button3, 480, 220);
	gtk_widget_set_size_request(button3, 110, 50);
	gtk_widget_set_tooltip_text(button3, "Click to add a word");
	g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(addWord), NULL);

	button4 = gtk_button_new_with_label("Delete word");
	gtk_widget_set_name(button4, "button2");
	gtk_fixed_put(GTK_FIXED(fixed), button4, 350, 280);
	gtk_widget_set_size_request(button4, 110, 50);
	gtk_widget_set_tooltip_text(button4, "Click to delete a word");
	g_signal_connect(G_OBJECT(button4), "clicked", G_CALLBACK(deleteWord), NULL);

	button5 = gtk_button_new_with_label("Library");
	gtk_widget_set_name(button5, "button2");
	gtk_fixed_put(GTK_FIXED(fixed), button5, 480, 280);
	gtk_widget_set_size_request(button5, 110, 50);
	gtk_widget_set_tooltip_text(button5, "Library");
	g_signal_connect(G_OBJECT(button5), "clicked", G_CALLBACK(library), NULL);

	button6 = gtk_button_new_with_label("Restore");
	gtk_widget_set_name(button6, "button2");
	gtk_fixed_put(GTK_FIXED(fixed), button6, 350, 340);
	gtk_widget_set_size_request(button6, 110, 50);
	gtk_widget_set_tooltip_text(button6, "Restore");
	g_signal_connect(G_OBJECT(button6), "clicked", G_CALLBACK(restore), NULL);

	button7 = gtk_button_new_with_label("Our team");
	gtk_widget_set_name(button7, "button2");
	gtk_fixed_put(GTK_FIXED(fixed), button7, 480, 340);
	gtk_widget_set_size_request(button7, 110, 50);
	gtk_widget_set_tooltip_text(button7, "Click here to meet our team");
	g_signal_connect(G_OBJECT(button7), "clicked", G_CALLBACK(team), NULL);

	button8 = gtk_button_new_with_label("Exit");
	gtk_widget_set_name(button8, "button1");
	gtk_fixed_put(GTK_FIXED(fixed), button8, 350, 400);
	gtk_widget_set_size_request(button8, 240, 50);
	g_signal_connect_swapped(button8, "clicked", G_CALLBACK(gtk_widget_destroy), window);

	ALLEGRO_SAMPLE *sample=NULL;
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(1);
	sample = al_load_sample("Img/Orange-7-Shigatsu-wa-kimi-no-uso.wav" );
	al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
	al_rest(0.0);

	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	gtk_widget_show_all(window);
	gtk_main();
	btcls(libraryTree);
	btcls(dictionary);
	return 0;
}

int convert_text_to_bt(char *filename){
    FILE * datafile;
    BTA *convertfile;
    convertfile = btcrt("data/evdic.dat", 0, 0);
	datafile = fopen(filename, "r");

    char word[WORD_MAX], mean[MEAN_MAX];
    int line;

    while (fscanf(datafile, "%[^\t]", word) == 1){
        fgets(mean, MEAN_MAX, datafile);
        line++;
        separate_mean(mean);
        btins(convertfile, word, mean, strlen(mean) + 1);    
    }
    btcls(convertfile);
    fclose(datafile);
    return 1;
}

void separate_mean(char* mean){
    int i = 0, j = 1;
    while (mean[j] != '\0'){
        if (mean[j] == '\\' && mean[j + 1] == 'n'){
            mean[i++] = '\n';
            j += 2;
        }
        else{
            if(i != j)
                mean[i++] = mean[j++];
            else{
                i++; j++;
            }
	    }
	}
	mean[i] = '\0';
}

void myCSS(void){
	GtkCssProvider *provider;
	GdkDisplay *display;
	GdkScreen *screen;

	provider = gtk_css_provider_new();//new css provider(cung cap)
	display = gdk_display_get_default();
	screen = gdk_display_get_default_screen(display);
	gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	const gchar *myCssFile = "mystyle.css";
	GError *error = 0;

	gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
	g_object_unref(provider);
}

void sourceTutorial(){
	GtkWidget *window1, *fixed, *label, *image;
	const gchar *info = "- <a href=\"https://github.com\">Github</a>\n- <a href=\"http://stackoverflow.com\">Stackoverflow</a>\n- <a href=\"https://developer.gnome.org/gtk3/\">GTK 3.0+ documentation</a>\n- <a href=\"https://www.allegro.cc/manual/5/\">Allegro 5 documentation</a>";

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);//create a new GtkWindow
	gtk_window_set_title(GTK_WINDOW(window1), "Source");//set the title of the GtkWindow
	gtk_window_set_default_size(GTK_WINDOW(window1), 220, 308);//set size of GtkWindow
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();//create new fixed
	gtk_container_add(GTK_CONTAINER(window1), fixed);

	image = gtk_image_new_from_file("Img/kaori2.jpg");//them anh tu file
	gtk_container_add(GTK_CONTAINER(fixed), image);

	label = gtk_label_new(NULL);
	gtk_fixed_put(GTK_FIXED(fixed), label, 20, 20);
	gtk_label_set_markup(GTK_LABEL(label), info);	

	gtk_widget_show_all(window1);
}

void searchTutorial(){
	GtkWidget *window1, *fixed, *fixed2, *scrolling;
	GtkWidget *label;
	GtkWidget *image, *image1, *image2;
	GtkWidget *button1, *button2;
	GtkWidget *textView1, *textView2;
	GtkTextBuffer *buffer1, *buffer2;

	myCSS();

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);//create a new GtkWindow
	gtk_window_set_title(GTK_WINDOW(window1), "Search Tutorial");//set the title of the GtkWindow
	gtk_window_set_default_size(GTK_WINDOW(window1), 800, 600);//set size of GtkWindow
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();//create new fixed
	gtk_container_add(GTK_CONTAINER(window1), fixed);

	image = gtk_image_new_from_file("Img/kaori3.jpg");//them anh tu file
	gtk_container_add(GTK_CONTAINER(fixed), image);

	scrolling = gtk_scrolled_window_new(NULL, NULL);
	gtk_fixed_put(GTK_FIXED(fixed), scrolling, 0, 0);
	gtk_widget_set_size_request(scrolling, 800, 600);

	fixed2 = gtk_fixed_new();//create new fixed
	gtk_container_add(GTK_CONTAINER(scrolling), fixed2);

	label = gtk_label_new("Search Tutorial");
	gtk_widget_set_name(label, "labelTitleSearchTutorial");
	gtk_fixed_put(GTK_FIXED(fixed2), label, 270, 20);

	buffer1 = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(buffer1, "Step 1: Enter word into search blank.", -1);
	textView1 = gtk_text_view_new_with_buffer(buffer1);
	gtk_widget_set_name(textView1, "textViewSearchTutorial");
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textView1), FALSE);
	gtk_fixed_put(GTK_FIXED(fixed2), textView1, 20, 80);
	gtk_widget_set_size_request(textView1, 760, 60);


	image1 = gtk_image_new_from_file("Img/searchInterface1.png");
	button1 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button1), image1);
	gtk_widget_set_name(button1, "buttonSearchTutorial");
	gtk_fixed_put(GTK_FIXED(fixed2), button1, 20, 120);
	gtk_widget_set_size_request(button1, 750, 507);

	buffer2 = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(buffer2, "Step 2: Press search button.", -1);
	textView2 = gtk_text_view_new_with_buffer(buffer2);
	gtk_widget_set_name(textView2, "textViewSearchTutorial");
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textView2), FALSE);
	gtk_fixed_put(GTK_FIXED(fixed2), textView2, 20, 660);
	gtk_widget_set_size_request(textView2, 760, 60);

	image2 = gtk_image_new_from_file("Img/searchInterface2.png");
	button2 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button2), image2);
	gtk_widget_set_name(button2, "buttonSearchTutorial");
	gtk_fixed_put(GTK_FIXED(fixed2), button2, 20, 710);
	gtk_widget_set_size_request(button2, 750, 507);

	gtk_widget_show_all(window1);
}

void editTutorial(){
	GtkWidget *window1, *fixed, *fixed2, *scrolling;
	GtkWidget *label;
	GtkWidget *image, *image1, *image2, *image3;
	GtkWidget *button1, *button2, *button3;
	GtkWidget *textView1, *textView2, *textView3;
	GtkTextBuffer *buffer1, *buffer2, *buffer3;

	myCSS();

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);//create a new GtkWindow
	gtk_window_set_title(GTK_WINDOW(window1), "Edit Tutorial");//set the title of the GtkWindow
	gtk_window_set_default_size(GTK_WINDOW(window1), 800, 600);//set size of GtkWindow
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();//create new fixed
	gtk_container_add(GTK_CONTAINER(window1), fixed);

	image = gtk_image_new_from_file("Img/kaori5.jpg");//them anh tu file
	gtk_container_add(GTK_CONTAINER(fixed), image);

	scrolling = gtk_scrolled_window_new(NULL, NULL);
	gtk_fixed_put(GTK_FIXED(fixed), scrolling, 0, 0);
	gtk_widget_set_size_request(scrolling, 800, 600);

	fixed2 = gtk_fixed_new();//create new fixed
	gtk_container_add(GTK_CONTAINER(scrolling), fixed2);

	label = gtk_label_new("Edit Tutorial");
	gtk_widget_set_name(label, "labelTitleSearchTutorial");
	gtk_fixed_put(GTK_FIXED(fixed2), label, 280, 20);

	buffer1 = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(buffer1, "Step 1: Click on mean blank", -1);
	textView1 = gtk_text_view_new_with_buffer(buffer1);
	gtk_widget_set_name(textView1, "textViewSearchTutorial");
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textView1), FALSE);
	gtk_fixed_put(GTK_FIXED(fixed2), textView1, 20, 80);
	gtk_widget_set_size_request(textView1, 760, 60);

	image1 = gtk_image_new_from_file("Img/editInterface1.png");
	button1 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button1), image1);
	gtk_widget_set_name(button1, "buttonSearchTutorial");
	gtk_fixed_put(GTK_FIXED(fixed2), button1, 20, 120);
	gtk_widget_set_size_request(button1, 750, 507);

	buffer2 = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(buffer2, "Step 2: Edit meaning here.", -1);
	textView2 = gtk_text_view_new_with_buffer(buffer2);
	gtk_widget_set_name(textView2, "textViewSearchTutorial");
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textView2), FALSE);
	gtk_fixed_put(GTK_FIXED(fixed2), textView2, 20, 660);
	gtk_widget_set_size_request(textView2, 760, 60);

	image2 = gtk_image_new_from_file("Img/editInterface2.png");
	button2 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button2), image2);
	gtk_widget_set_name(button2, "buttonSearchTutorial");
	gtk_fixed_put(GTK_FIXED(fixed2), button2, 20, 710);
	gtk_widget_set_size_request(button2, 750, 507);

	buffer3 = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(buffer3, "Step 3: Press update meaning button", -1);
	textView3 = gtk_text_view_new_with_buffer(buffer3);
	gtk_widget_set_name(textView3, "textViewSearchTutorial");
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textView3), FALSE);
	gtk_fixed_put(GTK_FIXED(fixed2), textView3, 20, 1220);
	gtk_widget_set_size_request(textView3, 760, 60);

	image3 = gtk_image_new_from_file("Img/editInterface3.png");
	button3 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button3), image3);
	gtk_widget_set_name(button3, "buttonSearchTutorial");
	gtk_fixed_put(GTK_FIXED(fixed2), button3, 20, 1260);
	gtk_widget_set_size_request(button3, 750, 507);

	gtk_widget_show_all(window1);
}

void libraryTutorial(){
	GtkWidget *window1, *fixed, *fixed2, *scrolling;
	GtkWidget *label;
	GtkWidget *image, *image1, *image2, *image3;
	GtkWidget *button1, *button2, *button3;
	GtkWidget *textView1, *textView2, *textView3;
	GtkTextBuffer *buffer1, *buffer2, *buffer3;

	myCSS();

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);//create a new GtkWindow
	gtk_window_set_title(GTK_WINDOW(window1), "Library Tutorial");//set the title of the GtkWindow
	gtk_window_set_default_size(GTK_WINDOW(window1), 800, 600);//set size of GtkWindow
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();//create new fixed
	gtk_container_add(GTK_CONTAINER(window1), fixed);

	image = gtk_image_new_from_file("Img/fantasticFour2.jpg");//them anh tu file
	gtk_container_add(GTK_CONTAINER(fixed), image);

	scrolling = gtk_scrolled_window_new(NULL, NULL);
	gtk_fixed_put(GTK_FIXED(fixed), scrolling, 0, 0);
	gtk_widget_set_size_request(scrolling, 800, 600);

	fixed2 = gtk_fixed_new();//create new fixed
	gtk_container_add(GTK_CONTAINER(scrolling), fixed2);

	label = gtk_label_new("Library Tutorial");
	gtk_widget_set_name(label, "labelTitleSearchTutorial");
	gtk_fixed_put(GTK_FIXED(fixed2), label, 270, 20);

	buffer1 = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(buffer1, "Press add to library button to add word to library.", -1);
	textView1 = gtk_text_view_new_with_buffer(buffer1);
	gtk_widget_set_name(textView1, "textViewSearchTutorial");
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textView1), FALSE);
	gtk_fixed_put(GTK_FIXED(fixed2), textView1, 20, 80);
	gtk_widget_set_size_request(textView1, 760, 60);

	image1 = gtk_image_new_from_file("Img/libraryInterface1.png");
	button1 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button1), image1);
	gtk_widget_set_name(button1, "buttonSearchTutorial");
	gtk_fixed_put(GTK_FIXED(fixed2), button1, 20, 120);
	gtk_widget_set_size_request(button1, 750, 507);

	buffer2 = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(buffer2, "Press remove from library button to remove word from library.", -1);
	textView2 = gtk_text_view_new_with_buffer(buffer2);
	gtk_widget_set_name(textView2, "textViewSearchTutorial");
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textView2), FALSE);
	gtk_fixed_put(GTK_FIXED(fixed2), textView2, 20, 660);
	gtk_widget_set_size_request(textView2, 760, 60);

	image2 = gtk_image_new_from_file("Img/libraryInterface2.png");
	button2 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button2), image2);
	gtk_widget_set_name(button2, "buttonSearchTutorial");
	gtk_fixed_put(GTK_FIXED(fixed2), button2, 20, 710);
	gtk_widget_set_size_request(button2, 750, 507);

	buffer3 = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(buffer3, "Press remove all button to remove all word from library.", -1);
	textView3 = gtk_text_view_new_with_buffer(buffer3);
	gtk_widget_set_name(textView3, "textViewSearchTutorial");
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textView3), FALSE);
	gtk_fixed_put(GTK_FIXED(fixed2), textView3, 20, 1200);
	gtk_widget_set_size_request(textView3, 760, 60);

	image3 = gtk_image_new_from_file("Img/libraryInterface3.png");
	button3 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button3), image3);
	gtk_widget_set_name(button3, "buttonSearchTutorial");
	gtk_fixed_put(GTK_FIXED(fixed2), button3, 100, 1240);
	gtk_widget_set_size_request(button3, 600, 530);

	gtk_widget_show_all(window1);
}

void addTutorial(){
	GtkWidget *window1, *fixed, *fixed2, *scrolling;
	GtkWidget *label;
	GtkWidget *image, *image1, *image2;
	GtkWidget *button1, *button2;
	GtkWidget *textView1, *textView2;
	GtkTextBuffer *buffer1, *buffer2;

	myCSS();

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);//create a new GtkWindow
	gtk_window_set_title(GTK_WINDOW(window1), "Add Tutorial");//set the title of the GtkWindow
	gtk_window_set_default_size(GTK_WINDOW(window1), 800, 600);//set size of GtkWindow
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();//create new fixed
	gtk_container_add(GTK_CONTAINER(window1), fixed);

	image = gtk_image_new_from_file("Img/kaoriandkousei3.jpg");//them anh tu file
	gtk_container_add(GTK_CONTAINER(fixed), image);

	scrolling = gtk_scrolled_window_new(NULL, NULL);
	gtk_fixed_put(GTK_FIXED(fixed), scrolling, 0, 0);
	gtk_widget_set_size_request(scrolling, 800, 600);

	fixed2 = gtk_fixed_new();//create new fixed
	gtk_container_add(GTK_CONTAINER(scrolling), fixed2);

	label = gtk_label_new("Add Tutorial");
	gtk_widget_set_name(label, "labelTitleSearchTutorial");
	gtk_fixed_put(GTK_FIXED(fixed2), label, 280, 20);

	buffer1 = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(buffer1, "Step 1: Enter word into input blank and meaning blank.", -1);
	textView1 = gtk_text_view_new_with_buffer(buffer1);
	gtk_widget_set_name(textView1, "textViewSearchTutorial");
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textView1), FALSE);
	gtk_fixed_put(GTK_FIXED(fixed2), textView1, 20, 80);
	gtk_widget_set_size_request(textView1, 760, 60);

	image1 = gtk_image_new_from_file("Img/addInterface1.png");
	button1 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button1), image1);
	gtk_widget_set_name(button1, "buttonSearchTutorial");
	gtk_fixed_put(GTK_FIXED(fixed2), button1, 20, 120);
	gtk_widget_set_size_request(button1, 750, 497);

	buffer2 = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(buffer2, "Step 2: Press add button.", -1);
	textView2 = gtk_text_view_new_with_buffer(buffer2);
	gtk_widget_set_name(textView2, "textViewSearchTutorial");
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textView2), FALSE);
	gtk_fixed_put(GTK_FIXED(fixed2), textView2, 20, 650);
	gtk_widget_set_size_request(textView2, 760, 60);

	image2 = gtk_image_new_from_file("Img/addInterface2.png");
	button2 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button2), image2);
	gtk_widget_set_name(button2, "buttonSearchTutorial");
	gtk_fixed_put(GTK_FIXED(fixed2), button2, 20, 680);
	gtk_widget_set_size_request(button2, 750, 497);

	gtk_widget_show_all(window1);
}

void deleteTutorial(){
	GtkWidget *window1, *fixed, *fixed2, *scrolling;
	GtkWidget *label;
	GtkWidget *image, *image1, *image2;
	GtkWidget *button1, *button2;
	GtkWidget *textView1, *textView2;
	GtkTextBuffer *buffer1, *buffer2;

	myCSS();

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);//create a new GtkWindow
	gtk_window_set_title(GTK_WINDOW(window1), "Search Tutorial");//set the title of the GtkWindow
	gtk_window_set_default_size(GTK_WINDOW(window1), 564, 564);//set size of GtkWindow
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();//create new fixed
	gtk_container_add(GTK_CONTAINER(window1), fixed);

	image = gtk_image_new_from_file("Img/kaori6.jpg");//them anh tu file
	gtk_container_add(GTK_CONTAINER(fixed), image);

	scrolling = gtk_scrolled_window_new(NULL, NULL);
	gtk_fixed_put(GTK_FIXED(fixed), scrolling, 0, 0);
	gtk_widget_set_size_request(scrolling, 564, 564);

	fixed2 = gtk_fixed_new();//create new fixed
	gtk_container_add(GTK_CONTAINER(scrolling), fixed2);

	label = gtk_label_new("Delete Tutorial");
	gtk_widget_set_name(label, "labelTitleSearchTutorial");
	gtk_fixed_put(GTK_FIXED(fixed2), label, 270, 20);

	buffer1 = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(buffer1, "Step 1: Enter word into input blank.", -1);
	textView1 = gtk_text_view_new_with_buffer(buffer1);
	gtk_widget_set_name(textView1, "textViewSearchTutorial");
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textView1), FALSE);
	gtk_fixed_put(GTK_FIXED(fixed2), textView1, 20, 80);
	gtk_widget_set_size_request(textView1, 564, 60);


	image1 = gtk_image_new_from_file("Img/deleteInterface1.png");
	button1 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button1), image1);
	gtk_widget_set_name(button1, "buttonSearchTutorial");
	gtk_fixed_put(GTK_FIXED(fixed2), button1, 0, 120);
	gtk_widget_set_size_request(button1, 564, 429);

	buffer2 = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(buffer2, "Step 2: Press search button.", -1);
	textView2 = gtk_text_view_new_with_buffer(buffer2);
	gtk_widget_set_name(textView2, "textViewSearchTutorial");
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textView2), FALSE);
	gtk_fixed_put(GTK_FIXED(fixed2), textView2, 20, 620);
	gtk_widget_set_size_request(textView2, 564, 60);

	image2 = gtk_image_new_from_file("Img/deleteInterface2.png");
	button2 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button2), image2);
	gtk_widget_set_name(button2, "buttonSearchTutorial");
	gtk_fixed_put(GTK_FIXED(fixed2), button2, 0, 660);
	gtk_widget_set_size_request(button2, 564, 429);

	gtk_widget_show_all(window1);
}

void tutorial(GtkWidget widget, gpointer window){
	GtkWidget *window1, *image, *fixed, *fixed2, *button1, *button2, *button3, *button4, *button5, *button6, *button7, *button8;
	GtkWidget *image1, *image2, *image3, *image4, *image5, *image6, *image7, *image8;
	GtkWidget *scrolling;

	myCSS();

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);//create a new GtkWindow
	gtk_window_set_title(GTK_WINDOW(window1), "Tutorial");//set the title of the GtkWindow
	gtk_window_set_default_size(GTK_WINDOW(window1), 750, 420);//set size of GtkWindow
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();//create new fixed
	gtk_container_add(GTK_CONTAINER(window1), fixed);//add widget to container
	image = gtk_image_new_from_file("Img/fantasticFour.jpg");//them anh tu file
	gtk_container_add(GTK_CONTAINER(fixed), image);
	gtk_widget_set_name(image, "image");

	scrolling = gtk_scrolled_window_new(NULL, NULL);
	gtk_fixed_put(GTK_FIXED(fixed), scrolling, 0, 0);
	gtk_widget_set_size_request(scrolling, 750, 400);

	fixed2 = gtk_fixed_new();//create new fixed
	gtk_container_add(GTK_CONTAINER(scrolling), fixed2);

	image1 = gtk_image_new_from_file("Img/sourceButton.png");
	button1 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button1), image1);
	gtk_fixed_put(GTK_FIXED(fixed2), button1, 15, 20);
	gtk_widget_set_name(button1, "buttonTutorial");
	gtk_widget_set_size_request(button1, 200, 200);
	gtk_widget_set_tooltip_text(button1, "Source");
	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(sourceTutorial), NULL);
	
	image2 = gtk_image_new_from_file("Img/searchButton.png");
	button2 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button2), image2);
	gtk_fixed_put(GTK_FIXED(fixed2), button2, 255, 20);
	gtk_widget_set_name(button2, "buttonTutorial");
	gtk_widget_set_size_request(button2, 200, 200);
	gtk_widget_set_tooltip_text(button2, "How to search word");
	g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(searchTutorial), NULL);

	image3 = gtk_image_new_from_file("Img/addButton.png");
	button3 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button3), image3);
	gtk_fixed_put(GTK_FIXED(fixed2), button3, 495, 20);
	gtk_widget_set_name(button3, "buttonTutorial");
	gtk_widget_set_size_request(button3, 200, 200);
	gtk_widget_set_tooltip_text(button3, "How to add word");
	g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(addTutorial), NULL);

	image4 = gtk_image_new_from_file("Img/editButton.png");
	button4 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button4), image4);
	gtk_fixed_put(GTK_FIXED(fixed2), button4, 15, 260);
	gtk_widget_set_name(button4, "buttonTutorial");
	gtk_widget_set_size_request(button4, 200, 200);
	gtk_widget_set_tooltip_text(button4, "How to edit mean");
	g_signal_connect(G_OBJECT(button4), "clicked", G_CALLBACK(editTutorial), NULL);
	
	image5 = gtk_image_new_from_file("Img/deleteButton.png");
	button5 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button5), image5);
	gtk_fixed_put(GTK_FIXED(fixed2), button5, 255, 260);
	gtk_widget_set_name(button5, "buttonTutorial");
	gtk_widget_set_size_request(button5, 200, 200);
	gtk_widget_set_tooltip_text(button5, "How to delete word");
	g_signal_connect(G_OBJECT(button5), "clicked", G_CALLBACK(deleteTutorial), NULL);

	image6 = gtk_image_new_from_file("Img/libraryButton.png");
	button6 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button6), image6);
	gtk_fixed_put(GTK_FIXED(fixed2), button6, 495, 260);
	gtk_widget_set_name(button6, "buttonTutorial");
	gtk_widget_set_size_request(button6, 200, 200);
	gtk_widget_set_tooltip_text(button6, "How to use library");
	g_signal_connect(G_OBJECT(button6), "clicked", G_CALLBACK(libraryTutorial), NULL);

	image7 = gtk_image_new_from_file("Img/restoreButton.png");
	button7 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button7), image7);
	gtk_fixed_put(GTK_FIXED(fixed2), button7, 15, 500);
	gtk_widget_set_name(button7, "buttonTutorial");
	gtk_widget_set_size_request(button7, 200, 200);
	gtk_widget_set_tooltip_text(button7, "How to restore dictionary");
	
	image8 = gtk_image_new_from_file("Img/teamButton.png");
	button8 = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button8), image8);
	gtk_fixed_put(GTK_FIXED(fixed2), button8, 255, 500);
	gtk_widget_set_name(button8, "buttonTutorial");
	gtk_widget_set_size_request(button8, 200, 200);
	gtk_widget_set_tooltip_text(button8, "How to see our team");

	gtk_widget_show_all(window1);
}

void setTextView(char *text){//add word to caching
	GtkTextBuffer *buffer;
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
	//return GtkTextBuffer dc hien thi boi text view
	if(buffer == NULL)
		buffer = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(buffer, text, -1);//thay gtri buffer = text
	gtk_text_view_set_buffer(GTK_TEXT_VIEW(textView), buffer);
	//set buffer khi hien thi bo nho dem dc hien thi boi text view
}

const char* soundex(const char *s){
	static char out[5];
	int c, prev, i;

	out[0] = out[4] = 0;
	if(!s || !*s) return out;

	out[0] = *s++;

	/* first letter, though not coded, can still affect next letter: Pfister */
	prev = code[(int)out[0]];
	for(i = 1; *s && i < 4; s++){
		if((c = code[(int) * s]) == prev) continue;
		if(c == -1) prev = 0;	/* vowel as separator */
		else if(c > 0){
			out[i++] = c + '0';
			prev = c;
		}
	}
	while(i < 4) out[i++] = '0';
	return out;
}

int prefix(const char *big, const char *small){// tra lai 1 neu giong prefix, 0 neu nguoc lai
	int small_len = strlen(small);
	int big_len = strlen(big);
	int i;
	if(big_len < small_len)
		return 0;
	for(i = 0; i < small_len; i++)
		if(big[i] != small[i])
			return 0;
	return 1;    
}

int commond_char(char * str1, char * str2, int start){
	int i;
	int slen1 = strlen(str1);
	int slen2 = strlen(str2);
	int slen  = (slen1 < slen2) ? slen1 : slen2;
	for( i = start; i < slen; i++)
		if(str1[i] != str2[i])
			return i;
	return i;
}

void jrb_to_list(JRB nextWordArray, int number){
   	GtkTreeIter Iter;
   	JRB tmp;
   	int sochia = number / 9;
   	int max = 8;
   	if(sochia == 0) sochia = 1;
   	jrb_traverse(tmp, nextWordArray){
  		if((number--) % sochia == 0){
     		gtk_list_store_append(GTK_LIST_STORE(list), &Iter);
     		gtk_list_store_set(GTK_LIST_STORE(list), &Iter, 0, jval_s(tmp->key), -1 );
     		if(max-- < 1)
     			return;
     	}
    }
}

int insert_insoundexlist(char *soundexlist , char *newword,  char *word, char *soundexWord){// tao newword voi ma soundex
	if(strcmp(soundexWord, soundex(newword)) == 0){
		if(strcmp(newword, word) != 0){
			strcat(soundexlist, newword);
			strcat(soundexlist, "\n");
			return 1;
		}
	}
	return 0;
}

void suggest(char * word, gboolean Tab_pressed){// suggest, dua vao prefix, dung JRB to list ~
	char nextword[100], prevword[100];
	int i, NumOfCommondChar, minNumOfCommondChar = 1000;
	int max;
	GtkTreeIter Iter;
	JRB tmp, nextWordArray = make_jrb();
	BTint value, existed = 0;
	strcpy(nextword, word);
	int wordlen = strlen(word);
	gtk_list_store_clear(GTK_LIST_STORE(list));
	if(bfndky(dictionary, word, &value) ==  0){ // tim word trong dictionary, value la gia tri cua 'word' tim duoc
		existed = 1;
		gtk_list_store_append(GTK_LIST_STORE(list), &Iter);
		gtk_list_store_set(GTK_LIST_STORE(list), &Iter, 0, nextword, -1 ); // neu dung thi ok
	}
	if(!existed)
		btins(dictionary, nextword, "", 1); // chen key va data vao B-tree, o lay chen blank vao !

	for(i = 0; i < 1945; i++){
		bnxtky(dictionary, nextword, &value);  // tim 'key' tiep theo
		if(prefix(nextword, word)){ // tim nhung tu co prefix giong
			jrb_insert_str(nextWordArray, strdup(nextword), JNULL);  // va chen vao array nextword (de show ra list -> jrb_to_list)
		}
		else break;
	}

	if(!existed && Tab_pressed){// an tab de ra tu goi y xD!
		if(jrb_empty(nextWordArray)){
			char soundexlist[1000] = "Ý bạn là:\n";
			char soundexWord[50];
			strcpy(nextword, word);
			strcpy(prevword, word);
			strcpy(soundexWord, soundex(word)); // soundex dung de tim tu 'xung quanh'
			max = 5;
			for(i = 0; (i < 10000) && max; i++){
				if(bprvky(dictionary , prevword, &value) == 0)
					if(insert_insoundexlist(soundexlist, prevword, word, soundexWord))
						max--;
			}
			max = 5;
			for(i = 0; (i < 10000) && max; i++){
				if(bnxtky(dictionary, nextword, &value) == 0)
					if(insert_insoundexlist(soundexlist, nextword, word, soundexWord))
						max--;
			}
			setTextView(soundexlist);
		}
		else{
			strcpy(nextword, jval_s(jrb_first(nextWordArray)->key));
			jrb_traverse(tmp, nextWordArray){
				NumOfCommondChar = commond_char(nextword, jval_s(tmp->key), wordlen);
				if(minNumOfCommondChar > NumOfCommondChar)
					minNumOfCommondChar = NumOfCommondChar;
			}

			if((minNumOfCommondChar != 1000) && (minNumOfCommondChar > wordlen)) {
				nextword[NumOfCommondChar] = '\0';
				gtk_entry_set_text(GTK_ENTRY(entry_search), nextword);
				gtk_editable_set_position(GTK_EDITABLE(entry_search), NumOfCommondChar);
			}
		}
	}
	else
		jrb_to_list(nextWordArray, i);
	if(!existed)
		btdel(dictionary, word);
	jrb_free_tree(nextWordArray);
}

gboolean search_suggest(GtkWidget * entry, GdkEvent * event, gpointer No_need){// gioi han ky tu, chi nhan alphabelt va tab
	GdkEventKey *keyEvent = (GdkEventKey*)event;
	char word[50];
	int len;
	strcpy(word, gtk_entry_get_text(GTK_ENTRY(entry_search)));
	if(keyEvent->keyval == GDK_KEY_Tab) suggest(word, TRUE);
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
		suggest(word, FALSE);
	}
	return FALSE;
}

static void search(GtkWidget *w, gpointer data){
	GtkWidget *entry1 = ((GtkWidget**)data)[0];
	GtkWidget *window1 = ((GtkWidget**)data)[1];

	a = gtk_entry_get_text(GTK_ENTRY(entry1));
	g_print("%s\n",a);
	char word[50];

	strcpy(word, a);
	if(word[0] == '\0')
		Message(GTK_WIDGET(window1), GTK_MESSAGE_WARNING, "Warning!", "Input is left blank!");
	else{
		int result = btfind(word);
		if(result == 0)
			Message(GTK_WIDGET(window1), GTK_MESSAGE_ERROR, "Error!","Word not found!");
	}
	return;
}

void Message(GtkWidget *parent, GtkMessageType type, char *mms, char *content){//Dua ra thong bao
	GtkWidget *mdialog;
	mdialog = gtk_message_dialog_new(GTK_WINDOW(parent), GTK_DIALOG_DESTROY_WITH_PARENT, type, GTK_BUTTONS_OK, "%s", mms);//
	gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(mdialog), "%s",  content);
	gtk_dialog_run(GTK_DIALOG(mdialog));
	gtk_widget_destroy(mdialog);
}

int btfind(char *word){// dung cho ham search
	char mean[100000];
	int size;

	if(btsel(dictionary, word, mean, 100000, &size) == 0){
		setTextView(mean);
		return 1;
	}
    else
    	return 0;
}

static void edit( GtkWidget *w, gpointer data){// ham chuc nang edit
	GtkWidget *entry1= ((GtkWidget**)data)[0];
	GtkWidget *window1=((GtkWidget**)data)[1];
	GtkWidget *edit_view=((GtkWidget**)data)[2];

	BTint x;

	if(gtk_entry_get_text(GTK_ENTRY(entry1))[0] == 0 || bfndky(dictionary, (char*)gtk_entry_get_text(GTK_ENTRY(entry1)), &x) != 0){
		Message(window1, GTK_MESSAGE_WARNING, "Warning", "Input is left blank!"); // Message o tren
		return;
	}

	a = gtk_entry_get_text(GTK_ENTRY(entry1));
	// g_print("%s\n",a);
	char word[50],mean[100000];
	strcpy(word,a);

	GtkTextBuffer *buffer2;
	GtkTextIter start, end, iter;

	buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(GTK_TEXT_VIEW(edit_view)));
	gtk_text_buffer_get_iter_at_offset(buffer2, &iter, 0);

	gtk_text_buffer_insert(buffer2, &iter, "", -1);
	gtk_text_buffer_get_bounds (buffer2, &start, &end);
	b = gtk_text_buffer_get_text (buffer2, &start, &end, FALSE);

	strcpy(mean,b);

	if(word[0] == '\0' || mean[0] == '\0')
		Message(GTK_WIDGET(window1), GTK_MESSAGE_WARNING, "Warning!", "No part is left blank!");
	else if(bfndky(dictionary, word, &x ) != 0)
		Message(GTK_WIDGET(window1), GTK_MESSAGE_ERROR, "Error", "Word not found!");
	else{
		if(btupd(dictionary, word, mean, strlen(mean) + 1) == 1)
			Message(GTK_WIDGET(window1),GTK_MESSAGE_ERROR, "Error","Can not update!");
		else
			Message(GTK_WIDGET(window1),GTK_MESSAGE_INFO, "Success!","Updated!");
	}
}

void addToLibrary(GtkWidget *w, gpointer data){
	GtkWidget *entry1= ((GtkWidget**)data)[0];
	GtkWidget *window1=((GtkWidget**)data)[1];

	a = gtk_entry_get_text(GTK_ENTRY(entry1));
	char word[50];
	strcpy(word,a);

	BTint x;

	if(bfndky(libraryTree, word, &x) != 0){
		binsky(libraryTree, word, 0);
		Message(GTK_WIDGET(window1),GTK_MESSAGE_INFO, "Success!","Added!");
	}
	else Message(GTK_WIDGET(window1),GTK_MESSAGE_INFO, "Notification!","Word already in library!");
}

void removeFromLibrary(GtkWidget *w, gpointer data){
	GtkWidget *entry1= ((GtkWidget**)data)[0];
	GtkWidget *window1=((GtkWidget**)data)[1];

	BTint x;

	a = gtk_entry_get_text(GTK_ENTRY(entry1));g_print("%s",a);
	char word[50];
	strcpy(word,a);
	if(bfndky(libraryTree, word, &x) != 0) Message(GTK_WIDGET(window1),GTK_MESSAGE_INFO, "Notification!","Word is not exist in library!");
	else{
		bdelky(libraryTree, word);
		Message(GTK_WIDGET(window1),GTK_MESSAGE_INFO, "Success!","Removed!");
	}
}

void close_window(GtkWidget *widget, gpointer window){
	gtk_widget_destroy(GTK_WIDGET(window));
}

void searchWord(GtkWidget widget, gpointer window){
	GtkWidget *fixed, *image;
	GtkWidget *button1,*window1,*label,*button2,*button3,*button4,*button5,*label2;

	myCSS();

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(window1, "window1");
	gtk_window_set_title(GTK_WINDOW(window1), "Search");
	gtk_window_set_default_size(GTK_WINDOW(window1), 750, 470);
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window1), fixed);

	label = gtk_label_new("Input:");
	gtk_fixed_put(GTK_FIXED(fixed), label, 30, 30);

	entry_search = gtk_entry_new();
	gtk_widget_set_size_request(entry_search, 300, 30);
	gtk_fixed_put(GTK_FIXED(fixed), entry_search, 100, 25);
	gtk_entry_set_max_length(GTK_ENTRY(entry_search), 100);
	gtk_widget_set_name(entry_search, "entry_search");

	GtkEntryCompletion *comple = gtk_entry_completion_new();
	gtk_entry_completion_set_text_column(comple, 0);
	list = gtk_list_store_new(10, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	gtk_entry_completion_set_model(comple, GTK_TREE_MODEL(list));
	gtk_entry_set_completion(GTK_ENTRY(entry_search), comple);

	button1 = gtk_button_new_with_label("Search");
	gtk_widget_set_name(button1, "buttonSearch");
	gtk_fixed_put(GTK_FIXED(fixed), button1, 450, 15);
	gtk_widget_set_size_request(button1, 90, 30);

	label2 = gtk_label_new("Meaning:");
	gtk_fixed_put(GTK_FIXED(fixed), label2, 30, 200);

	GtkWidget *scrolling = gtk_scrolled_window_new(NULL, NULL);
	gtk_fixed_put(GTK_FIXED(fixed), scrolling, 100, 100);
	gtk_widget_set_size_request(scrolling, 300, 300);

	textView = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scrolling), textView);
	gtk_widget_set_name(textView, "textView");

	button2 = gtk_button_new_with_label("Back");
	gtk_widget_set_name(button2, "buttonBack");
	gtk_fixed_put(GTK_FIXED(fixed), button2, 560, 15);
	gtk_widget_set_size_request(button2, 90, 30);

	button4 = gtk_button_new_with_label("Add to library");
	gtk_widget_set_name(button4, "buttonSave");
	gtk_fixed_put(GTK_FIXED(fixed), button4, 450, 50);
	gtk_widget_set_size_request(button4, 200, 30);

	button5 = gtk_button_new_with_label("Remove from library");
	gtk_widget_set_name(button5, "buttonRemove");
	gtk_fixed_put(GTK_FIXED(fixed), button5, 450, 85);
	gtk_widget_set_size_request(button5, 200, 30);

	button3 = gtk_button_new_with_label("Update meaning");
	gtk_widget_set_name(button3, "buttonUpt");
	gtk_fixed_put(GTK_FIXED(fixed), button3, 450, 120);
	gtk_widget_set_size_request(button3, 200, 30);

	image = gtk_image_new_from_file("Img/kaori.jpg");
	gtk_fixed_put(GTK_FIXED(fixed), image, 450, 160);
	gtk_container_add(GTK_CONTAINER(fixed), image);

	GtkWidget *data[3];
	data[0]= entry_search;
	data[1]= window1;
	data[2]= textView;

	g_signal_connect(entry_search, "key-press-event", G_CALLBACK(search_suggest), NULL);
	g_signal_connect(G_OBJECT(entry_search), "activate", G_CALLBACK(search), data);
	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(search), data);
	g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(close_window), window1);
	g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(edit), data);
	g_signal_connect(G_OBJECT(button4), "clicked", G_CALLBACK(addToLibrary), data);
	g_signal_connect(G_OBJECT(button5), "clicked", G_CALLBACK(removeFromLibrary), data);
	g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window1);
	gtk_main();

	return;
}

static void add(GtkWidget *w, gpointer data){
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

static void del(GtkWidget *w, gpointer data){
	GtkWidget *entry1= ((GtkWidget**)data)[0];
	GtkWidget *window1=((GtkWidget**)data)[1];

	a = gtk_entry_get_text(GTK_ENTRY(entry1));
	g_print("%s\n",a);
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

	image = gtk_image_new_from_file("Img/kousei.jpg");
	gtk_fixed_put(GTK_FIXED(fixed), image, 450, 80);

	gtk_widget_show_all(window1);

	gtk_main();

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

	image = gtk_image_new_from_file("Img/kaori4.jpg");
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

void restore(){
	btcls(dictionary);
	FILE *fin, *fout;
	fin = fopen("data/evdic2.dat", "rb");
	fout = fopen("data/evdic.dat", "wb");
	
	size_t n, m;
    unsigned char buff[8192];
    do{
        n = fread(buff, 1, sizeof(buff), fin);
        if(n) m = fwrite(buff, 1, n, fout);
        else m = 0;
    }while((n > 0) && (n == m));
	fclose(fin);
	fclose(fout);
	dictionary = btopn("data/evdic.dat", 0, 1);
	Message(GTK_WIDGET(window),GTK_MESSAGE_INFO, "Success!","Restored!");
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

void removeAll(){
	char word[50];
	char* x = NULL;
	int size;
	btsel(libraryTree, "", word, sizeof(char) * (strlen(word) + 1), &size); bdelky(libraryTree, word);
    while(btseln(libraryTree, word, x, 0, &size) == 0) bdelky(libraryTree, word);
}

void library(GtkWidget widget, gpointer window){
	GtkWidget *window1, *scrolling, *button, *scrolling2[100], *fixed, *fixed2, *fixed3, *label, *label2, *image;
	
	char word[50], mean[100000];
	int count = 1, size;
	char* x = NULL;

	myCSS();

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	// gtk_widget_set_name(window1, "window3");
	gtk_window_set_title(GTK_WINDOW(window1), "Library");
	gtk_window_set_default_size(GTK_WINDOW(window1), 600, 500);
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window1), fixed);

	image = gtk_image_new_from_file("Img/tsubaki.jpg");//them anh tu file
	gtk_container_add(GTK_CONTAINER(fixed), image);

	button = gtk_button_new_with_label("Remove all");
	gtk_widget_set_name(button, "buttonRemoveAll");
	gtk_fixed_put(GTK_FIXED(fixed), button, 20, 20);
	gtk_widget_set_size_request(button, 80, 80);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(removeAll), window1);

	scrolling = gtk_scrolled_window_new(NULL, NULL);
	gtk_fixed_put(GTK_FIXED(fixed), scrolling, 350, 20);
	gtk_widget_set_size_request(scrolling, 250, 450);

	fixed2 = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(scrolling), fixed2);

	btsel(libraryTree, "", word, sizeof(char) * (strlen(word) + 1), &size);
    while(btseln(libraryTree, word, x, 0, &size) == 0){
		btsel(dictionary, word, mean, 100000, &size);
		scrolling2[count] = gtk_scrolled_window_new(NULL, NULL);
		gtk_widget_set_name(scrolling2[count], "scrolling");
		gtk_fixed_put(GTK_FIXED(fixed2), scrolling2[count], 0, -120+120*count);
		gtk_widget_set_size_request(scrolling2[count], 345, 100);
		fixed3 = gtk_fixed_new();
		gtk_container_add(GTK_CONTAINER(scrolling2[count]), fixed3);
		label = gtk_label_new(word);
		gtk_fixed_put(GTK_FIXED(fixed3), label, 0, 0);
		label2 = gtk_label_new(mean);
		gtk_fixed_put(GTK_FIXED(fixed3), label2, 0, 15);
		count++;
	}
	gtk_widget_show_all(window1);
}

void team(GtkWidget widget, gpointer window){
	GtkWidget *image1, *image2, *label1, *label2, *button1, *button2, *window1, *fixed, *image3;
	const gchar *info1 = "Phạm Hữu An\nContact me: <a href=\"https://www.facebook.com/supersmartpog\">Facebook</a>, <a href=\"mailto:phaman3899@gmail.com\">Gmail</a>";
	const gchar *info2 = "Đoàn Ngọc Chiến\nContact me: <a href=\"https://www.facebook.com/100004695601749\">Facebook</a>, <a href=\"mailto:chiendoanngoc1705@gmail.com\">Gmail</a>";

	myCSS();

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(window1, "window3");
	gtk_window_set_title(GTK_WINDOW(window1), "About team");
	gtk_window_set_default_size(GTK_WINDOW(window1), 500, 240);
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window1), fixed);

	button1 = gtk_button_new();
	gtk_fixed_put(GTK_FIXED(fixed), button1, 20, 20);
	gtk_widget_set_size_request(button1, 80, 80);
	image1 = gtk_image_new_from_file("Img/an.jpg");
	gtk_widget_set_tooltip_text(button1, "Click here see more");
	gtk_container_add(GTK_CONTAINER(button1), image1);
	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(phamhuuan), NULL);
	label1 = gtk_label_new(NULL);
	gtk_fixed_put(GTK_FIXED(fixed), label1, 120, 50);
	gtk_label_set_markup(GTK_LABEL(label1), info1);

	button2 = gtk_button_new();
	gtk_fixed_put(GTK_FIXED(fixed), button2, 20, 120);
	gtk_widget_set_size_request(button2, 80, 80);
	image2 = gtk_image_new_from_file("Img/chien.jpg");
	gtk_widget_set_tooltip_text(button2, "Click here see more");
	gtk_container_add(GTK_CONTAINER(button2), image2);
	g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(doanngocchien), NULL);
	label2 = gtk_label_new(NULL);
	gtk_fixed_put(GTK_FIXED(fixed), label2, 120, 150);
	gtk_label_set_markup(GTK_LABEL(label2), info2);

	image3 = gtk_image_new_from_file("Img/kaoriandkousei.jpg");
	gtk_fixed_put(GTK_FIXED(fixed), image3, 350, 0);
	gtk_container_add(GTK_CONTAINER(fixed), image3);

	gtk_widget_show_all(window1);
}