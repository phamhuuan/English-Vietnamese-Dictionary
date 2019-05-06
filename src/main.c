#include <gtk/gtk.h>
#include <stdio.h>																															
#include <stdlib.h>
#include <string.h>
#include "../inc/btree.h"
#include "jrb.h"
#include <gdk/gdkkeysyms.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "extern.h"
#include "setTextView.c"
#include "message.c"
#include "closeWindow.c"
#include "tutorial.c"
#include "myCSS.c"
#include "textToBtree.c"
#include "search.c"
#include "team.c"
#include "library.c"
#include "add.c"
#include "delete.c"
#include "restore.c"
#include "setting.c"

//Khai bao
const gchar *a, *b;
ALLEGRO_SAMPLE *sample = NULL;
ALLEGRO_SAMPLE_INSTANCE* instance;
BTA *dictionary = NULL;
BTA *libraryTree = NULL;
int i = 0;
FILE *fileSettingMusic;

// typedef struct settingMusic;
// typedef struct settingMusic{
// 	int mute;
// 	float vol;
// }SettingMusic;

GtkWidget *textView, *buttonLibraryTextView, *view1, *view2, *about_dialog, *entry_search;
GtkWidget *window;
SettingMusic s;

int main(int argc, char *argv[]){
	btinit();
	dictionary = btopn("../data/evdic.dat", 0, 1);//cho phep update va share
	if(dictionary == NULL){
		g_print("Waiting for creating data...\n");
		convert_text_to_bt("../data/AnhViet.txt");
		dictionary = btopn("../data/evdic.dat", 0, 1);
		g_print("Done!\n");
	}
	libraryTree = btopn("../data/library.dat", 0, 1);
	GtkWidget *image, *image2, *fixed;
	GtkWidget *button1, *button2, *button3, *button4, *button5, *button6, *button7, *button8, *button9;

	gtk_init(&argc, &argv);//khoi tao gtk

	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(1);
	sample = al_load_sample("../Img/Orange-7-Shigatsu-wa-kimi-no-uso.wav");
	instance = al_create_sample_instance(sample);
	al_attach_sample_instance_to_mixer(instance, al_get_default_mixer());
	al_set_sample_instance_playing(instance, true);
	fileSettingMusic = fopen("../data/settingMusic.dat", "rb");
	fread(&s, sizeof(s), 1, fileSettingMusic);
	fclose(fileSettingMusic);
	if(s.mute == 1) al_set_sample_instance_gain(instance, 0.0);
	else al_set_sample_instance_gain(instance, s.vol);
	al_set_sample_instance_playmode(instance, ALLEGRO_PLAYMODE_LOOP);
	al_rest(0.0);

	/*Tao cua so*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//create a new GtkWindow
	gtk_window_set_title(GTK_WINDOW(window), "English-Vietnamese Dictionary");//set the title of the GtkWindow
	gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);//set size of GtkWindow
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);//Cua so se xuat hien o giua man hinh


	/*Tao hinh nen*/
	fixed = gtk_fixed_new();//create new fixed
	gtk_container_add(GTK_CONTAINER(window), fixed);//add widget to container
	image = gtk_image_new_from_file("../Img/shigatsuwakiminouso2.jpg");//them anh tu file
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

	button9 = gtk_button_new();
	image2 = gtk_image_new_from_file("../Img/setting.png");
	gtk_button_set_image(GTK_BUTTON(button9), image2);
	gtk_widget_set_name(button9, "button2");
	gtk_fixed_put(GTK_FIXED(fixed), button9, 20, 20);
	gtk_widget_set_size_request(button9, 40, 40);
	gtk_widget_set_tooltip_text(button9, "Setting");
	g_signal_connect(button9, "clicked", G_CALLBACK(setting), NULL);

	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	gtk_widget_show_all(window);
	gtk_main();
	btcls(libraryTree);
	btcls(dictionary);
	return 0;
}