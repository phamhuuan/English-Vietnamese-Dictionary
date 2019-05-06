void restore();

void restore(){
	btcls(dictionary);
	FILE *fin, *fout;
	fin = fopen("../data/evdic2.dat", "rb");
	fout = fopen("../data/evdic.dat", "wb");
	
	size_t n, m;
    unsigned char buff[8192];
    do{
        n = fread(buff, 1, sizeof(buff), fin);
        if(n) m = fwrite(buff, 1, n, fout);
        else m = 0;
    }while((n > 0) && (n == m));
	fclose(fin);
	fclose(fout);
	dictionary = btopn("../data/evdic.dat", 0, 1);
	Message(GTK_WIDGET(window),GTK_MESSAGE_INFO, "Success!","Restored!");
}