void setTextView(char* text, GtkTextView *textView);

void setTextView(char *text, GtkTextView *textView){//add word to caching
	GtkTextBuffer *buffer;
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
	//return GtkTextBuffer dc hien thi boi text view
	if(buffer == NULL)
		buffer = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(buffer, text, -1);//thay gtri buffer = text
	gtk_text_view_set_buffer(GTK_TEXT_VIEW(textView), buffer);
	//set buffer khi hien thi bo nho dem dc hien thi boi text view
}