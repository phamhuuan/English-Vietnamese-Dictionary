void onOffMusic();
void changeVolume(GtkRange *range, gpointer data);
void setting(GtkWidget widget, gpointer window);
void changeTheme();
void loginLogout();
void registerChangePass();
void initMainSetting();
void checkUsername(GtkWidget *entry, GdkEvent *event);
void checkPhoneNum(GtkWidget *entry, GdkEvent *event);
void checkEmail(GtkWidget *entry, GdkEvent *event);
void checkPassword(GtkWidget *entry, GdkEvent *event);
void checkRepassword(GtkWidget *entry, GdkEvent *event);
void userRegister(gpointer data);
void userLogin();
void changePass();
void keepLogIn(GtkToggleButton *toggle_button, gpointer data);
void showHidePass(GtkWidget *button, gpointer *data);

GtkWidget *button1, *button4, *button5, *label1;
char password[50];
char username[50];
char phoneNum[15];
char email[50];

int check1 = 0, check2 = 0, check3 = 0, check4 = 0, check5 = 0;

GtkWidget *spinButton1;
GtkAdjustment *adjustment;
GtkAdjustment *hadjustment;
GtkWidget *hScale;
GtkWidget *labelR, *label1R, *label2R, *label3R, *label4R, *label5R, *buttonR, *fixedR;
GtkWidget *button1R, *button2R, *button3R, *button4R;
GtkWidget *entry1R, *entry2R, *entry3R, *entry4R, *entry5R;
GtkWidget *labelL;
GtkWidget *entry1L, *entry2L, *checkButton;
GtkWidget *window1L;
GtkWidget *fixedL;
GtkWidget *label1L;
GtkWidget *button1L, *buttonL, *button2L, *button3L;

GtkWidget *window1R;

int showHidePassL;

void onOffMusic(){
    GtkWidget *image1;
    fileSettingMusic = fopen("../data/settingMusic.dat", "rb");
    fscanf(fileSettingMusic, "%d %f", &s.mute, &s.vol);
    fclose(fileSettingMusic);
	if(s.mute == 1){//dang mute --> k mute
		al_set_sample_instance_gain(instance, s.vol);
        image1 = gtk_image_new_from_file("../Img/unmute.png");
        gtk_widget_set_tooltip_text(button1, "Click here to mute");
        gtk_button_set_image(GTK_BUTTON(button1), image1);
        s.mute = 0;
	}
	else{
		al_set_sample_instance_gain(instance, 0.0);
        image1 = gtk_image_new_from_file("../Img/mute.png");
        gtk_widget_set_tooltip_text(button1, "Click here to unmute");
        gtk_button_set_image(GTK_BUTTON(button1), image1);
		s.mute = 1;
	}
    fileSettingMusic = fopen("../data/settingMusic.dat", "wb");
    fprintf(fileSettingMusic, "%d %f", s.mute, s.vol);
    fclose(fileSettingMusic);
}

void changeVolume(GtkRange *range, gpointer data){
    gdouble pos = gtk_range_get_value(range);
    s.vol = pos / 100;
    if(s.mute == 1){
        s.mute = 0;
        image1 = gtk_image_new_from_file("../Img/unmute.png");
        gtk_widget_set_tooltip_text(button1, "Click here to mute");
        gtk_button_set_image(GTK_BUTTON(button1), image1);
    }
    fileSettingMusic = fopen("../data/settingMusic.dat", "wb");
    fprintf(fileSettingMusic, "%d %f", s.mute, s.vol);
    fclose(fileSettingMusic);
    al_set_sample_instance_gain(instance, s.vol);
    gchar *str = g_strdup_printf("Volume %.0f", pos);
    gtk_label_set_text(GTK_LABEL(label1), str);
}

void changeTheme(){
    theme = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(spinButton1));
    fileSettingTheme = fopen("../data/settingTheme.dat", "wb");
    fprintf(fileSettingTheme, "%d", theme);
    fclose(fileSettingTheme);
    if(theme == 1){
        gtk_image_set_from_file(GTK_IMAGE(image), "../Img/shigatsuwakiminouso2.jpg");
        al_destroy_sample_instance(instance);
        sample = al_load_sample("../Img/Orange7.wav");
        instance = al_create_sample_instance(sample);
        al_attach_sample_instance_to_mixer(instance, al_get_default_mixer());
        al_set_sample_instance_playing(instance, true);
        al_set_sample_instance_playmode(instance, ALLEGRO_PLAYMODE_LOOP);
        if(s.mute == 1) al_set_sample_instance_gain(instance, 0);
        else al_set_sample_instance_gain(instance, s.vol);
    }
    if(theme == 2){
        gtk_image_set_from_file(GTK_IMAGE(image), "../Img/tfwb1.jpg");
        al_destroy_sample_instance(instance);
        sample = al_load_sample("../Img/GotoubunNoKimochi.wav");
        instance = al_create_sample_instance(sample);
        al_attach_sample_instance_to_mixer(instance, al_get_default_mixer());
        al_set_sample_instance_playing(instance, true);
        al_set_sample_instance_playmode(instance, ALLEGRO_PLAYMODE_LOOP);
        if(s.mute == 1) al_set_sample_instance_gain(instance, 0);
        else al_set_sample_instance_gain(instance, s.vol);
    }
}

void userLogin(){
    GtkWidget *image1, *image2;
    char username[50], password[50];
    a = gtk_entry_get_text(GTK_ENTRY(entry1L));
    strcpy(username, a);
    a = gtk_entry_get_text(GTK_ENTRY(entry2L));
    strcpy(password, a);
    int found = 0;
    fileUser = fopen("../data/user.dat", "rb");
    while(fscanf(fileUser, "%s %s %s %s", userTmp.userName, userTmp.phoneNum, userTmp.emailAdr, userTmp.passWord) != EOF){
        if(strcmp(username, userTmp.userName) == 0){
            found = 1;
            if(strcmp(password, userTmp.passWord) == 0){
                isLogin = 1;
                fileIsLogIn = fopen("../data/isLogin.dat", "wb");
                fprintf(fileIsLogIn, "%d %s", isLogin, username);
                fclose(fileIsLogIn);
                Message(GTK_WIDGET(window1L),GTK_MESSAGE_INFO, "Success!","Login!");
                image1 = gtk_image_new_from_file("../Img/logout.png");
                gtk_button_set_image(GTK_BUTTON(button4), image1);
                gtk_window_close(GTK_WINDOW(window1L));

                image2 = gtk_image_new_from_file("../Img/changePass.png");
                gtk_button_set_image(GTK_BUTTON(button5), image2);

                gchar *str = g_strdup_printf("%s", username);
    	        gtk_label_set_text(GTK_LABEL(labelMain), str);
            }
            else{
                gtk_label_set_text(GTK_LABEL(label1L), "Wrong password");
                gtk_widget_set_name(label1L, "error");
            }
        }
    }
    if(found == 0){
        gtk_label_set_text(GTK_LABEL(label1L), "User not exists");
        gtk_widget_set_name(label1L, "error");
    }
}

void changePass(){
    char username[50], password[50], newpw1[50], newpw2[50];
    a = gtk_entry_get_text(GTK_ENTRY(entry1R));
    strcpy(username, a);
    a = gtk_entry_get_text(GTK_ENTRY(entry2R));
    strcpy(password, a);
    a = gtk_entry_get_text(GTK_ENTRY(entry3R));
    strcpy(newpw1, a);
    a = gtk_entry_get_text(GTK_ENTRY(entry4R));
    strcpy(newpw2, a);
    int found = 0;
    fileUser = fopen("../data/user.dat", "rb");
    while(fscanf(fileUser, "%s %s %s %s", userTmp.userName, userTmp.phoneNum, userTmp.emailAdr, userTmp.passWord) != EOF){
        if(strcmp(username, userTmp.userName) == 0){
            found = 1;
            if(strcmp(password, userTmp.passWord) == 0){
                if(strcmp(newpw1, newpw2) != 0){
                    gtk_label_set_text(GTK_LABEL(label1R), "New password not match");
                    gtk_widget_set_name(label1R, "error");
                    return;
                }
                break;
            }
            else{
                gtk_label_set_text(GTK_LABEL(label1R), "Wrong password");
                gtk_widget_set_name(label1R, "error");
                return;
            }
        }
    }
    if(found == 0){
        gtk_label_set_text(GTK_LABEL(label1R), "User not exists");
        gtk_widget_set_name(label1R, "error");
        return;
    }
    fclose(fileUser);
    copyFile("../data/user.dat", "../data/user2.dat");
    FILE *ftemp = fopen("../data/user2.dat", "rb");
    fileUser = fopen("../data/user.dat", "wb");
    while(fscanf(ftemp, "%s %s %s %s", userTmp.userName, userTmp.phoneNum, userTmp.emailAdr, userTmp.passWord) != EOF){
        if(strcmp(userTmp.userName, username) == 0) strcpy(userTmp.passWord, newpw1);
        fprintf(fileUser, "%s %s %s %s\n", userTmp.userName, userTmp.phoneNum, userTmp.emailAdr, userTmp.passWord);
    }
    Message(GTK_WIDGET(window1R),GTK_MESSAGE_INFO, "Success!","Password changed");
    fclose(ftemp);
    fclose(fileUser);
    gtk_window_close(GTK_WINDOW(window1L));
}

void keepLogIn(GtkToggleButton *toggle_button, gpointer data){
    if(gtk_toggle_button_get_active(toggle_button)){
        fileKeepLogIn = fopen("../data/keepLogin.dat", "wb");
        fprintf(fileKeepLogIn, "%d", 1);
        fclose(fileKeepLogIn);
    }
    else{
        fileKeepLogIn = fopen("../data/keepLogin.dat", "wb");
        fprintf(fileKeepLogIn, "%d", 0);
        fclose(fileKeepLogIn);
    }
}

void showHidePass(GtkWidget *button, gpointer *showPass){
    GtkWidget *image;
    if(*showPass == (gpointer)0){
        image = gtk_image_new_from_file("../Img/showPassword.png");
        gtk_button_set_image(GTK_BUTTON(button), image);
        *showPass = (gpointer)1;
        gtk_entry_set_visibility(GTK_ENTRY(entry2L), TRUE);
    }
    else if(*showPass == (gpointer)1){
        image = gtk_image_new_from_file("../Img/hidePassword.png");
        gtk_button_set_image(GTK_BUTTON(button), image);
        *showPass = (gpointer)0;
        gtk_entry_set_visibility(GTK_ENTRY(entry2L), FALSE);
    }
}

void loginLogout(){
    GtkWidget *image1, *image2, *image3;
    fileIsLogIn = fopen("../data/isLogin.dat", "rb");
    char tmp[50];
    fscanf(fileIsLogIn, "%d %s", &isLogin, tmp);
    fclose(fileIsLogIn);
    if(isLogin == 0){
        window1L = gtk_window_new(GTK_WINDOW_TOPLEVEL);//create a new GtkWindow
        gtk_window_set_title(GTK_WINDOW(window1L), "Login");//set the title of the GtkWindow
        gtk_window_set_default_size(GTK_WINDOW(window1L), 300, 300);//set size of GtkWindow
        gtk_window_set_position(GTK_WINDOW(window1L), GTK_WIN_POS_CENTER);

        fixedL = gtk_fixed_new();//create new fixed
        gtk_container_add(GTK_CONTAINER(window1L), fixedL);

        labelL = gtk_label_new("Login");
        gtk_fixed_put(GTK_FIXED(fixedL), labelL, 120, 30);

        entry1L = gtk_entry_new();
        gtk_widget_set_size_request(entry1L, 150, 30);
        gtk_fixed_put(GTK_FIXED(fixedL), entry1L, 70, 50);
        gtk_entry_set_max_length(GTK_ENTRY(entry1L), 50);
        gtk_entry_set_placeholder_text(GTK_ENTRY(entry1L), "Username");

        label1L = gtk_label_new("");
        gtk_fixed_put(GTK_FIXED(fixedL), label1L, 110, 120);

        entry2L = gtk_entry_new();
        gtk_widget_set_size_request(entry2L, 150, 30);
        gtk_fixed_put(GTK_FIXED(fixedL), entry2L, 70, 90);//administrator
        gtk_entry_set_max_length(GTK_ENTRY(entry2L), 14);
        gtk_entry_set_placeholder_text(GTK_ENTRY(entry2L), "Password");
        gtk_entry_set_visibility(GTK_ENTRY(entry2L), FALSE);

        button1L = gtk_button_new_with_label("Login");
        gtk_widget_set_size_request(button1L, 165, 30);
        gtk_fixed_put(GTK_FIXED(fixedL), button1L, 70, 160);

        buttonL = gtk_button_new_with_label("Back");
        gtk_widget_set_size_request(buttonL, 165, 30);
        gtk_fixed_put(GTK_FIXED(fixedL), buttonL, 70, 200);

        button2L = gtk_button_new();
        showHidePassL = 0;
        image3 = gtk_image_new_from_file("../Img/hidePassword.png");
        gtk_button_set_image(GTK_BUTTON(button2L), image3);
        gtk_fixed_put(GTK_FIXED(fixedL), button2L, 240, 90);
        gtk_widget_set_size_request(button2L, 20, 20);
        gtk_widget_set_name(button2L, "button2");

        g_signal_connect(G_OBJECT(button2L), "clicked", G_CALLBACK(showHidePass), (gpointer)&showHidePassL);

        checkButton = gtk_check_button_new_with_label("Keep login");
        gtk_fixed_put(GTK_FIXED(fixedL), checkButton, 100, 135);
        g_signal_connect (GTK_TOGGLE_BUTTON (checkButton), "toggled", G_CALLBACK(keepLogIn), window1L);

        g_signal_connect(G_OBJECT(button1L), "clicked", G_CALLBACK(userLogin), NULL);
        g_signal_connect(G_OBJECT(buttonL), "clicked", G_CALLBACK(close_window), window1L);
        
        gtk_widget_show_all(window1L);
    }
    else if(isLogin == 1){
        fileIsLogIn = fopen("../data/isLogin.dat", "wb");
        isLogin = 0;
        fprintf(fileIsLogIn, "%d %s", isLogin, "NONE");
        fclose(fileIsLogIn);
        image1 = gtk_image_new_from_file("../Img/login.png");
        gtk_button_set_image(GTK_BUTTON(button4), image1);

        image2 = gtk_image_new_from_file("../Img/register.png");
        gtk_button_set_image(GTK_BUTTON(button5), image2);
        
        gchar *str = g_strdup_printf("%s", "");
    	gtk_label_set_text(GTK_LABEL(labelMain), str);

        fileKeepLogIn = fopen("../data/keepLogin.dat", "wb");
        fprintf(fileKeepLogIn, "%d", 0);
        fclose(fileKeepLogIn);
    }
}

void checkUsername(GtkWidget *entry, GdkEvent *event){
    GdkEventKey *keyEvent = (GdkEventKey*)event;
    int len;
    check1 = 0;

    strcpy(username, gtk_entry_get_text(GTK_ENTRY(entry)));

	if(keyEvent->keyval != GDK_KEY_BackSpace){
		len = strlen(username);
		username[len] = keyEvent->keyval;
		username[len + 1] = '\0';
	}
	else{
		len = strlen(username);
		username[len - 1] = '\0';
	}

    if(strlen(username) == 0){
        gtk_label_set_text(GTK_LABEL(label1R), "*Compulsory");
        gtk_widget_set_name(label1R, "error");
    }
    else if(strlen(username) < 5){
        gtk_label_set_text(GTK_LABEL(label1R), "Username must at least 5 character");
        gtk_widget_set_name(label1R, "error");
    }
    else{
        fileUser = fopen("../data/user.dat", "rb");
        while(fscanf(fileUser, "%s %s %s %s", userTmp.userName, userTmp.phoneNum, userTmp.emailAdr, userTmp.passWord) != EOF){
            if(strcmp(username, userTmp.userName) == 0){
                gtk_label_set_text(GTK_LABEL(label1R), "Username exists");
                gtk_widget_set_name(label1R, "error");
            }
            else{
                gtk_label_set_text(GTK_LABEL(label1R), "Username availability");
                gtk_widget_set_name(label1R, "ok");
                check1 = 1;
            }
        }
        fclose(fileUser);
    }
}

void checkPhoneNum(GtkWidget *entry, GdkEvent *event){
    GdkEventKey *keyEvent = (GdkEventKey*)event;
    int len;
    check2 = 0;

    strcpy(phoneNum, gtk_entry_get_text(GTK_ENTRY(entry)));

	if(keyEvent->keyval != GDK_KEY_BackSpace){
		len = strlen(phoneNum);
		phoneNum[len] = keyEvent->keyval;
		phoneNum[len + 1] = '\0';
	}
	else{
		len = strlen(phoneNum);
		phoneNum[len - 1] = '\0';
	}
    int tmp = 1;

    for(int i = 0; i < strlen(phoneNum); i++)
        if(phoneNum[i] > '9' || phoneNum[i] < '0'){
            gtk_label_set_text(GTK_LABEL(label2R), "Invalid number");
            gtk_widget_set_name(label2R, "error");
            tmp = 0;
        }
    if(tmp == 1){
        if(strlen(phoneNum) == 0){
            gtk_label_set_text(GTK_LABEL(label2R), "*Compulsory");
            gtk_widget_set_name(label2R, "error");
        }
        else if(strlen(phoneNum) != 10){
            gtk_label_set_text(GTK_LABEL(label2R), "Invalid number");
            gtk_widget_set_name(label2R, "error");
        }
        else if(strlen(phoneNum) == 10){
            fileUser = fopen("../data/user.dat", "rb");
            while(fscanf(fileUser, "%s %s %s %s", userTmp.userName, userTmp.phoneNum, userTmp.emailAdr, userTmp.passWord) != EOF){
                if(strcmp(phoneNum, userTmp.phoneNum) == 0){
                    gtk_label_set_text(GTK_LABEL(label2R), "Phone number exists");
                    gtk_widget_set_name(label2R, "error");
                }
                else{
                    gtk_label_set_text(GTK_LABEL(label2R), "Phone number availability");
                    gtk_widget_set_name(label2R, "ok");
                    check2 = 1;
                }
            }
            fclose(fileUser);
        }
    }
}

void checkEmail(GtkWidget *entry, GdkEvent *event){
    GdkEventKey *keyEvent = (GdkEventKey*)event;
    int len;
    check3 = 0;

    strcpy(email, gtk_entry_get_text(GTK_ENTRY(entry)));

	if(keyEvent->keyval != GDK_KEY_BackSpace){
		len = strlen(email);
		email[len] = keyEvent->keyval;
		email[len + 1] = '\0';
	}
	else{
		len = strlen(email);
		email[len - 1] = '\0';
	}

    if(strlen(email) == 0){
        gtk_label_set_text(GTK_LABEL(label3R), "*Compulsory");
        gtk_widget_set_name(label3R, "error");
    }
    else{int dot=0,at=0,j=-1,dotCheck=0,i;
        for(i = 0; i < strlen(email); i++){
            if(email[i] == '!' || email[i] == '#' || email[i] == '$' || email[i] == '%' || email[i] == '&' ||
            email[i] == '*' || email[i] == '^' || email[i] == '(' || email[i] == ')' || email[i] == '+' || email[i] == '=' ||
            email[i] == ',' || email[i] == '/' || email[i] == '\\' || email[i] == '|' || email[i] == '~' || email[i] == '`' 
            || email[i] == '\'' || email[i] == '\"' || email[i] == ' ' || email[i] == '?' || email[i] == '<' || email[i] == '>'){
                gtk_label_set_text(GTK_LABEL(label3R), "Invalid email");
                gtk_widget_set_name(label3R, "error");
                return;
            }
            if(email[i] == '.'){
                dot++;
                if(email[i-1] == '.'){
                    gtk_label_set_text(GTK_LABEL(label3R), "Invalid email");
                    gtk_widget_set_name(label3R, "error");
                    return;
                }
                if(j != -1 && i > j) dotCheck = 1;
            }
            if(email[i] == '@'){
                at++;j=i;
                if(at > 1){
                    gtk_label_set_text(GTK_LABEL(label3R), "Invalid email");
                    gtk_widget_set_name(label3R, "error");
                    return;
                }
            }
        }
        if(dot == 0 || dotCheck == 0 || email[i-1] == '.'){
            gtk_label_set_text(GTK_LABEL(label3R), "Invalid email");
            gtk_widget_set_name(label3R, "error");
        }
        else{
            fileUser = fopen("../data/user.dat", "rb");
            while(fscanf(fileUser, "%s %s %s %s", userTmp.userName, userTmp.phoneNum, userTmp.emailAdr, userTmp.passWord) != EOF){
                if(strcmp(email, userTmp.emailAdr) == 0){
                    gtk_label_set_text(GTK_LABEL(label3R), "Email already in used");
                    gtk_widget_set_name(label3R, "error");
                }
                else{
                    gtk_label_set_text(GTK_LABEL(label3R), "Email availability");
                    gtk_widget_set_name(label3R, "ok");
                    check3 = 1;
                }
            }
            fclose(fileUser);
        }
    }
}

void checkPassword(GtkWidget *entry, GdkEvent *event){
    GdkEventKey *keyEvent = (GdkEventKey*)event;
    int len;
    check4 = 0;

    strcpy(password, gtk_entry_get_text(GTK_ENTRY(entry)));

	if(keyEvent->keyval != GDK_KEY_BackSpace){
		len = strlen(password);
		password[len] = keyEvent->keyval;
		password[len + 1] = '\0';
	}
	else{
		len = strlen(password);
		password[len - 1] = '\0';
	}

    if(strlen(password) == 0){
        gtk_label_set_text(GTK_LABEL(label4R), "*Compulsory");
        gtk_widget_set_name(label4R, "error");
    }
    else if(strlen(password) < 8){
        gtk_label_set_text(GTK_LABEL(label4R), "Password must at least 8 character");
        gtk_widget_set_name(label4R, "error");
    }
    else{
        gtk_label_set_text(GTK_LABEL(label4R), "Valid password");
        gtk_widget_set_name(label4R, "ok");
        check4 = 1;
    }
}

void checkRepassword(GtkWidget *entry, GdkEvent *event){
    GdkEventKey *keyEvent = (GdkEventKey*)event;
    int len;
    char repassword[50];
    check5 = 0;

    strcpy(repassword, gtk_entry_get_text(GTK_ENTRY(entry)));

	if(keyEvent->keyval != GDK_KEY_BackSpace){
		len = strlen(repassword);
		repassword[len] = keyEvent->keyval;
		repassword[len + 1] = '\0';
	}
	else{
		len = strlen(repassword);
		repassword[len - 1] = '\0';
	}

    if(strlen(repassword) == 0){
        gtk_label_set_text(GTK_LABEL(label5R), "*Compulsory");
        gtk_widget_set_name(label5R, "error");
    }
    else if(strcmp(repassword, password) == 0){
        gtk_label_set_text(GTK_LABEL(label5R), "Ok");
        gtk_widget_set_name(label5R, "ok");
        check5 = 1;
    }
    else{
        gtk_label_set_text(GTK_LABEL(label5R), "Wrong");
        gtk_widget_set_name(label5R, "error");
    }
}

void userRegister(gpointer data){
    fileUser = fopen("../data/user.dat", "ab");
    if(check1 == 1 && check2 == 1 && check3 == 1 && check4 == 1 && check5 == 1){
        fprintf(fileUser, "%s %s %s %s\n", username, phoneNum, email, password);
        Message(GTK_WIDGET(window1R),GTK_MESSAGE_INFO, "Success!","Registered!");
        check1 = 0;check2 = 0;check3 = 0;check4 = 0;check5 = 0;
        gtk_window_close(GTK_WINDOW(window1R));
    }
    else{
        Message(GTK_WIDGET(window1R), GTK_MESSAGE_ERROR, "Error", "Something went wrong!");
    }
    fclose(fileUser);
}

void registerChangePass(){
    fileIsLogIn = fopen("../data/isLogin.dat", "rb");
    char tmp[50];
    fscanf(fileIsLogIn, "%d %s", &isLogin, tmp);
    fclose(fileIsLogIn);
    if(isLogin == 0){
        window1R = gtk_window_new(GTK_WINDOW_TOPLEVEL);//create a new GtkWindow
        gtk_window_set_title(GTK_WINDOW(window1R), "Register");//set the title of the GtkWindow
        gtk_window_set_default_size(GTK_WINDOW(window1R), 400, 300);//set size of GtkWindow
        gtk_window_set_position(GTK_WINDOW(window1R), GTK_WIN_POS_CENTER);

        fixedR = gtk_fixed_new();//create new fixed
        gtk_container_add(GTK_CONTAINER(window1R), fixedR);

        buttonR = gtk_button_new_with_label("Back");
        gtk_fixed_put(GTK_FIXED(fixedR), buttonR, 200, 250);
        gtk_widget_set_size_request(buttonR, 150, 30);

        labelR = gtk_label_new("Register");
        gtk_fixed_put(GTK_FIXED(fixedR), labelR, 120, 30);

        label1R = gtk_label_new("*Compusory");
        gtk_widget_set_name(label1R, "error");
        gtk_fixed_put(GTK_FIXED(fixedR), label1R, 190, 55);

        entry1R = gtk_entry_new();
        gtk_widget_set_size_request(entry1R, 150, 30);
        gtk_fixed_put(GTK_FIXED(fixedR), entry1R, 20, 50);
        gtk_entry_set_max_length(GTK_ENTRY(entry1R), 50);
        gtk_entry_set_placeholder_text(GTK_ENTRY(entry1R), "Username");

        label2R = gtk_label_new("*Compusory");
        gtk_widget_set_name(label2R, "error");
        gtk_fixed_put(GTK_FIXED(fixedR), label2R, 190, 95);

        entry2R = gtk_entry_new();
        gtk_widget_set_size_request(entry2R, 150, 30);
        gtk_fixed_put(GTK_FIXED(fixedR), entry2R, 20, 90);//administrator
        gtk_entry_set_max_length(GTK_ENTRY(entry2R), 14);
        gtk_entry_set_placeholder_text(GTK_ENTRY(entry2R), "Phone number");

        label3R = gtk_label_new("*Compusory");
        gtk_widget_set_name(label3R, "error");
        gtk_fixed_put(GTK_FIXED(fixedR), label3R, 190, 135);

        entry3R = gtk_entry_new();
        gtk_widget_set_size_request(entry3R, 150, 30);
        gtk_fixed_put(GTK_FIXED(fixedR), entry3R, 20, 130);
        gtk_entry_set_max_length(GTK_ENTRY(entry3R), 50);
        gtk_entry_set_placeholder_text(GTK_ENTRY(entry3R), "Email");

        label4R = gtk_label_new("*Compusory");
        gtk_widget_set_name(label4R, "error");
        gtk_fixed_put(GTK_FIXED(fixedR), label4R, 190, 175);

        entry4R = gtk_entry_new();
        gtk_widget_set_size_request(entry4R, 150, 30);
        gtk_fixed_put(GTK_FIXED(fixedR), entry4R, 20, 170);
        gtk_entry_set_max_length(GTK_ENTRY(entry4R), 50);
        gtk_entry_set_placeholder_text(GTK_ENTRY(entry4R), "Password");
        gtk_entry_set_visibility(GTK_ENTRY(entry4R), FALSE);

        label5R = gtk_label_new("*Compusory");
        gtk_widget_set_name(label5R, "error");
        gtk_fixed_put(GTK_FIXED(fixedR), label5R, 190, 215);

        entry5R = gtk_entry_new();
        gtk_widget_set_size_request(entry5R, 150, 30);
        gtk_fixed_put(GTK_FIXED(fixedR), entry5R, 20, 210);
        gtk_entry_set_max_length(GTK_ENTRY(entry5R), 50);
        gtk_entry_set_placeholder_text(GTK_ENTRY(entry5R), "Password again");
        gtk_entry_set_visibility(GTK_ENTRY(entry5R), FALSE);

        button1R = gtk_button_new_with_label("Register");
        gtk_widget_set_size_request(button1R, 165, 30);
        gtk_fixed_put(GTK_FIXED(fixedR), button1R, 20, 250);

        g_signal_connect(entry1R, "key-press-event", G_CALLBACK(checkUsername), NULL);
        g_signal_connect(entry2R, "key-press-event", G_CALLBACK(checkPhoneNum), NULL);
        g_signal_connect(entry3R, "key-press-event", G_CALLBACK(checkEmail), NULL);
        g_signal_connect(entry4R, "key-press-event", G_CALLBACK(checkPassword), NULL);
        g_signal_connect(entry5R, "key-press-event", G_CALLBACK(checkRepassword), NULL);
        g_signal_connect(G_OBJECT(button1R), "clicked", G_CALLBACK(userRegister), NULL);
        g_signal_connect(G_OBJECT(buttonR), "clicked", G_CALLBACK(close_window), window1R);

        gtk_widget_show_all(window1R);
    }
    else{
        window1R = gtk_window_new(GTK_WINDOW_TOPLEVEL);//create a new GtkWindow
        gtk_window_set_title(GTK_WINDOW(window1R), "Change Password");//set the title of the GtkWindow
        gtk_window_set_default_size(GTK_WINDOW(window1R), 300, 300);//set size of GtkWindow
        gtk_window_set_position(GTK_WINDOW(window1R), GTK_WIN_POS_CENTER);

        fixedR = gtk_fixed_new();//create new fixed
        gtk_container_add(GTK_CONTAINER(window1R), fixedR);

        buttonR = gtk_button_new_with_label("Back");
        gtk_fixed_put(GTK_FIXED(fixedR), buttonR, 70, 250);
        gtk_widget_set_size_request(buttonR, 165, 30);

        labelR = gtk_label_new("Change password");
        gtk_fixed_put(GTK_FIXED(fixedR), labelR, 100, 30);

        label1R = gtk_label_new("");
        // gtk_widget_set_name(label1R, "error");
        gtk_fixed_put(GTK_FIXED(fixedR), label1R, 190, 55);

        entry1R = gtk_entry_new();
        gtk_widget_set_size_request(entry1R, 150, 30);
        gtk_fixed_put(GTK_FIXED(fixedR), entry1R, 70, 50);
        gtk_entry_set_max_length(GTK_ENTRY(entry1R), 50);
        gtk_entry_set_placeholder_text(GTK_ENTRY(entry1R), "Username");

        label2R = gtk_label_new("");
        // gtk_widget_set_name(label2R, "error");
        gtk_fixed_put(GTK_FIXED(fixedR), label2R, 190, 95);

        entry2R = gtk_entry_new();
        gtk_widget_set_size_request(entry2R, 150, 30);
        gtk_fixed_put(GTK_FIXED(fixedR), entry2R, 70, 90);//administrator
        gtk_entry_set_max_length(GTK_ENTRY(entry2R), 14);
        gtk_entry_set_placeholder_text(GTK_ENTRY(entry2R), "Old password");
        gtk_entry_set_visibility(GTK_ENTRY(entry2R), FALSE);

        label3R = gtk_label_new("");
        // gtk_widget_set_name(label3R, "error");
        gtk_fixed_put(GTK_FIXED(fixedR), label3R, 190, 135);

        entry3R = gtk_entry_new();
        gtk_widget_set_size_request(entry3R, 150, 30);
        gtk_fixed_put(GTK_FIXED(fixedR), entry3R, 70, 130);
        gtk_entry_set_max_length(GTK_ENTRY(entry3R), 50);
        gtk_entry_set_placeholder_text(GTK_ENTRY(entry3R), "New password");
        gtk_entry_set_visibility(GTK_ENTRY(entry3R), FALSE);

        label4R = gtk_label_new("");
        // gtk_widget_set_name(label4R, "error");
        gtk_fixed_put(GTK_FIXED(fixedR), label4R, 190, 175);

        entry4R = gtk_entry_new();
        gtk_widget_set_size_request(entry4R, 150, 30);
        gtk_fixed_put(GTK_FIXED(fixedR), entry4R, 70, 170);
        gtk_entry_set_max_length(GTK_ENTRY(entry4R), 50);
        gtk_entry_set_placeholder_text(GTK_ENTRY(entry4R), "Renew Password");
        gtk_entry_set_visibility(GTK_ENTRY(entry4R), FALSE);

        button1R = gtk_button_new_with_label("Change");
        gtk_widget_set_size_request(button1R, 165, 30);
        gtk_fixed_put(GTK_FIXED(fixedR), button1R, 70, 210);

        g_signal_connect(G_OBJECT(button1R), "clicked", G_CALLBACK(changePass), NULL);
        g_signal_connect(G_OBJECT(buttonR), "clicked", G_CALLBACK(close_window), window1R);

        gtk_widget_show_all(window1R);
    }
}

void setting(GtkWidget widget, gpointer window){
    GtkWidget *window1;
    GtkWidget *image1, *image2, *image3, *image4, *image5;
    GtkWidget *fixed;
    GtkWidget *button2, *button3;
    // image = gtk_image_new_from_file("../Img/tfwb1.jpg");
    fileSettingMusic = fopen("../data/settingMusic.dat", "rb");
    fscanf(fileSettingMusic, "%d %f", &s.mute, &s.vol);
    fclose(fileSettingMusic);

	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);//create a new GtkWindow
	gtk_window_set_title(GTK_WINDOW(window1), "Setting");//set the title of the GtkWindow
	gtk_window_set_default_size(GTK_WINDOW(window1), 300, 300);//set size of GtkWindow
	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window1), FALSE);

	fixed = gtk_fixed_new();//create new fixed
	gtk_container_add(GTK_CONTAINER(window1), fixed);

	button1 = gtk_button_new();
	if(s.mute == 1){
		image1 = gtk_image_new_from_file("../Img/mute.png");
		gtk_widget_set_tooltip_text(button1, "Click here to unmute");
	}
	else{
		image1 = gtk_image_new_from_file("../Img/unmute.png");
		gtk_widget_set_tooltip_text(button1, "Click here to mute");
	}
	gtk_button_set_image(GTK_BUTTON(button1), image1);
	gtk_widget_set_name(button1, "button2");
	gtk_fixed_put(GTK_FIXED(fixed), button1, 20, 20);
	gtk_widget_set_size_request(button1, 40, 40);

	g_signal_connect(button1, "clicked", G_CALLBACK(onOffMusic), NULL);

    button2 = gtk_button_new();
    image2 = gtk_image_new_from_file("../Img/settingVolume.png");
    gtk_button_set_image(GTK_BUTTON(button2), image2);
	gtk_widget_set_name(button2, "button2");
    gtk_fixed_put(GTK_FIXED(fixed), button2, 20, 80);
	gtk_widget_set_size_request(button2, 40, 40);

    hadjustment = gtk_adjustment_new (s.vol * 100, 0, 100, 1, 0, 0);
    hScale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, hadjustment);
    gtk_scale_set_digits (GTK_SCALE(hScale), 0);
    gtk_widget_set_hexpand(hScale, TRUE);
    gtk_widget_set_valign(hScale, GTK_ALIGN_START);
    gtk_widget_set_name(hScale, "hScale");
    gtk_fixed_put(GTK_FIXED(fixed), hScale, 80, 80);

    label1 = gtk_label_new("");
    gchar *str = g_strdup_printf("Volume: %.0f", s.vol * 100);
    gtk_label_set_text(GTK_LABEL(label1), str);
    gtk_fixed_put(GTK_FIXED(fixed), label1, 140, 105);

    button3 = gtk_button_new();
    image3 = gtk_image_new_from_file("../Img/settingTheme.png");
    gtk_button_set_image(GTK_BUTTON(button3), image3);
	gtk_widget_set_name(button3, "button2");
    gtk_fixed_put(GTK_FIXED(fixed), button3, 20, 140);
	gtk_widget_set_size_request(button3, 40, 40);

    fileSettingTheme = fopen("../data/settingTheme.dat", "rb");
    fscanf(fileSettingTheme, "%d", &theme);
    fclose(fileSettingTheme);

    adjustment = gtk_adjustment_new(theme, 1, 2, 1, 0, 0);//khoi tao - start - end - step - page_increment - page_size
    spinButton1 = gtk_spin_button_new(adjustment, 1, 0);
    gtk_widget_set_name(spinButton1, "spinButton1");
    gtk_fixed_put(GTK_FIXED(fixed), spinButton1, 80, 150);

    g_signal_connect(hScale, "value-changed", G_CALLBACK(changeVolume), NULL);
    g_signal_connect(spinButton1, "value-changed", G_CALLBACK(changeTheme), NULL);

    fileIsLogIn = fopen("../data/isLogin.dat", "rb");
    char tmp[50];
    fscanf(fileIsLogIn, "%d %s", &isLogin, tmp);
    fclose(fileIsLogIn);
    button4 = gtk_button_new();
    if(isLogin == 0) image4 = gtk_image_new_from_file("../Img/login.png");
    if(isLogin == 1) image4 = gtk_image_new_from_file("../Img/logout.png");
    gtk_button_set_image(GTK_BUTTON(button4), image4);
    gtk_widget_set_name(button3, "button2");
    gtk_fixed_put(GTK_FIXED(fixed), button4, 20, 200);
	gtk_widget_set_size_request(button4, 120, 40);

    button5 = gtk_button_new();
    if(isLogin == 0) image5 = gtk_image_new_from_file("../Img/register.png");
    if(isLogin == 1) image5 = gtk_image_new_from_file("../Img/changePass.png");
    gtk_button_set_image(GTK_BUTTON(button5), image5);
    gtk_widget_set_name(button3, "button2");
    gtk_fixed_put(GTK_FIXED(fixed), button5, 160, 200);
	gtk_widget_set_size_request(button5, 120, 40);

    g_signal_connect(button4, "clicked", G_CALLBACK(loginLogout), NULL);
    g_signal_connect(button5, "clicked", G_CALLBACK(registerChangePass), NULL);

	gtk_widget_show_all(window1);
}