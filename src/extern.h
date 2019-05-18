extern BTA *dictionary;
extern BTA *libraryTree;
extern BTA *soundexTree;
extern const gchar *a, *b;

extern int size;
extern int theme;

extern ALLEGRO_SAMPLE *sample;
extern ALLEGRO_SAMPLE_INSTANCE* instance;

extern GtkWidget *view, *textView, *buttonLibraryTextView, *view1, *view2, *about_dialog, *entry_search;
extern GtkWidget *window, *image, *labelMain;

extern int i;

extern FILE *fileSettingMusic;
extern FILE *fileHistory;
extern FILE *fileSettingTheme;
extern FILE *fileUser;
extern FILE *fileIsLogIn;
extern FILE *fileKeepLogIn;

extern char wordHistory[50];
extern char wordTmp[1000][50];

extern Dllist node, linkedList;

typedef struct settingMusic{
    int mute;
    float vol;
}SettingMusic;

extern SettingMusic s;

typedef struct User{
    char userName[80];
    char passWord[80];
    char phoneNum[15];
    char emailAdr[80];
}USER;

extern USER *user, userTmp;
extern int isLogin, keepLogin;