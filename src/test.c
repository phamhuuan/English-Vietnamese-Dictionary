#include <stdio.h>
#include <stdlib.h>

FILE *f;

int main(){
  f = fopen("../data/user.dat", "w+b");
  char a[50], b[50], c[50], d[50];
  // while(fscanf(f, "%s %s %s %s", a, b, c, d)!=EOF)
  // printf("%s %s %s %s\n", a, b, c, d);
  fprintf(f, "%s %s %s %s\n", "administrator", "0942437667", "phaman3899@gmail.com", "smartpog");
  fclose(f);
  return 0;
}