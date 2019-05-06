extern BTA* dictionary;
extern BTA *libraryTree;
extern const gchar *a, *b;

extern ALLEGRO_SAMPLE *sample;
extern ALLEGRO_SAMPLE_INSTANCE* instance;

extern GtkWidget *textView, *buttonLibraryTextView, *view1, *view2, *about_dialog, *entry_search;
extern GtkWidget *window;

extern int i;

extern FILE *fileSettingMusic;

typedef struct settingMusic{
    int mute;
    float vol;
}SettingMusic;

extern SettingMusic s;