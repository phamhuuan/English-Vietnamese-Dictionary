#include <stdio.h>																															
#include <stdlib.h>

// #include "extern.h"

// FILE *fileSettingMusic;

// typedef struct settingMusic{
// 	int mute;
// 	float vol;
// }SettingMusic;

// SettingMusic s;

int main(){
    // s.mute = 0, s.vol = 1.0;
    // fileSettingMusic = fopen("../data/settingMusic.dat", "wb");
	// fwrite(&s, sizeof(s), 1, fileSettingMusic);
    // // fread(&s, sizeof(s), 1, fileSettingMusic);
	// // printf("Mute %d, Vol %f\n", s.mute, s.vol);
    // fclose(fileSettingMusic);

    char str[][50] = {"Xin chao", "Toi la", "Pham Huu An"};

    printf("%s", str[0]);
}