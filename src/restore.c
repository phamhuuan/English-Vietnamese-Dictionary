void restore();

void restore(){
	fileIsLogIn = fopen("../data/isLogin.dat", "rb");
    char tmp[50];
    fscanf(fileIsLogIn, "%d %s", &isLogin, tmp);
    fclose(fileIsLogIn);
    if(isLogin == 0){
        Message(GTK_WIDGET(window),GTK_MESSAGE_INFO, "Notice","You need login to use this function");
        return;
    }
	btcls(dictionary);
    copyFile("../data/evdic2.dat", "../data/evdic.dat");
	dictionary = btopn("../data/evdic.dat", 0, 1);
	Message(GTK_WIDGET(window),GTK_MESSAGE_INFO, "Success!","Restored!");
}