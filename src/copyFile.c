#include <stdio.h>
#include <stdlib.h>

void copyFile(char *fileNameIn, char *fileNameOut);

void copyFile(char *fileNameIn, char *fileNameOut){
    FILE *fin, *fout;
    fin = fopen(fileNameIn, "rb");
    fout = fopen(fileNameOut, "wb");
    size_t n, m;
    unsigned char buff[8192];
    do{
        n = fread(buff, 1, sizeof(buff), fin);
        if(n) m = fwrite(buff, 1, n, fout);
        else m = 0;
    }while((n > 0) && (n == m));
	fclose(fin);
	fclose(fout);
}