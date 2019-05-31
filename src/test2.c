#include <stdio.h>
#include <stdlib.h>

long long countLine(FILE *f){
  char c; long long count = 0;
  while((c = fgetc(f)) != EOF) if(c == '\n') count++;
  return count + 1;
}

int main(){
  int sum = 0;
  FILE *f;
  f = fopen("add.c", "r");
  sum += countLine(f);
  fclose(f);
  f = fopen("closeWindow.c", "r");
  sum += countLine(f);
  fclose(f);
  f = fopen("delete.c", "r");
  sum += countLine(f);
  fclose(f);
  f = fopen("history.c", "r");
  sum += countLine(f);
  fclose(f);
  f = fopen("extern.h", "r");
  sum += countLine(f);
  fclose(f);
  f = fopen("library.c", "r");
  sum += countLine(f);
  fclose(f);
  f = fopen("main.c", "r");
  sum += countLine(f);
  fclose(f);
  f = fopen("message.c", "r");
  sum += countLine(f);
  fclose(f);
  f = fopen("myCSS.c", "r");
  sum += countLine(f);
  fclose(f);
  f = fopen("mystyle.css", "r");
  sum += countLine(f);
  fclose(f);
  f = fopen("restore.c", "r");
  sum += countLine(f);
  fclose(f);
  f = fopen("search.c", "r");
  sum += countLine(f);
  fclose(f);
  f = fopen("setTextView.c", "r");
  sum += countLine(f);
  fclose(f);
  f = fopen("setting.c", "r");
  sum += countLine(f);
  fclose(f);
  f = fopen("team.c", "r");
  sum += countLine(f);
  fclose(f);
  f = fopen("init.c", "r");
  sum += countLine(f);
  fclose(f);
  f = fopen("tutorial.c", "r");
  sum += countLine(f);
  fclose(f);
  f = fopen("copyFile.c", "r");
  sum += countLine(f);
  fclose(f);
  printf("%d\n", sum);
  return 0;
}