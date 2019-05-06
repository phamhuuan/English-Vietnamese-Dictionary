void Message(GtkWidget *parent, GtkMessageType type,  char *mms, char *content);

void Message(GtkWidget *parent, GtkMessageType type, char *mms, char *content){//Dua ra thong bao
	GtkWidget *mdialog;
	mdialog = gtk_message_dialog_new(GTK_WINDOW(parent), GTK_DIALOG_DESTROY_WITH_PARENT, type, GTK_BUTTONS_OK, "%s", mms);//
	gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(mdialog), "%s",  content);
	gtk_dialog_run(GTK_DIALOG(mdialog));
	gtk_widget_destroy(mdialog);
}