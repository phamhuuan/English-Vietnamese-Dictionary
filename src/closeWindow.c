void close_window(GtkWidget *widget, gpointer window);

void close_window(GtkWidget *widget, gpointer window){
	gtk_widget_destroy(GTK_WIDGET(window));
}