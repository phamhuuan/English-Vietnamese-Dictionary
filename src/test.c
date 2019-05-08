#include <stdio.h>																															
#include <stdlib.h>
#include <string.h>
// #include "extern.h"
#include "dllist.h"
#include "jval.h"
#include "../inc/btree.h"

FILE *fileSettingMusic;

typedef struct settingMusic{
	int word;
}SettingMusic;

SettingMusic s;

int main(){
    // btinit();int size;
    // BTA *test = NULL;
    // test = btopn("../data/historyBtree.dat", 0, 1);
    // char word[50], mean[1000];

    // btsel(test, "", NULL, 1, &size);int i=0;
    // while(btseln(test, word, NULL, 0, &size) == 0){printf("%d", i++);
    //     btsel(test, word, mean, 100000, &size);
    //     printf("%s\t\t%s\n", word, mean);
    // }
    // s.mute = 0, s.vol = 1.0;
    // strcpy(s.word, "");
    s.word = 1;
    fileSettingMusic = fopen("../data/settingTheme.dat", "w+b");
	fwrite(&s, sizeof(s), 1, fileSettingMusic);
    // fread(&s, sizeof(s), 1, fileSettingMusic);
	// printf("Mute %d\n", s.word);
    // while(fscanf(fileSettingMusic, "%s", s.word)!=EOF)printf("%s\n", s.word);
    fclose(fileSettingMusic);

    // char str[][50] = {"Xin chao", "Toi la", "Pham Huu An"};

    // printf("%s", str[0]);
    // Dllist node, list;
    // list = new_dllist();
    // while(1){
    //     gets(s.word);
    //     dll_append(list, new_jval_s(s.word));

    //     dll_traverse(node, list) printf("%s\n", jval_s(node->val));
    // }
    // do{dll_append(list, new_jval_s("Toi"));
    // dll_traverse(node, list) printf("%s\n", jval_s(node->val));
    // dll_append(list, new_jval_s("la"));
    // dll_traverse(node, list) printf("%s\n", jval_s(node->val));
    // dll_append(list, new_jval_s("An"));
    // dll_traverse(node, list) printf("%s\n", jval_s(node->val));
    // }while(0);
}