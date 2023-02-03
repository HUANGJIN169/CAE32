/*
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
int main(void) {

  system("wget https://github.com/janc18/CAE32/releases/download/test/Realese-v0.0.1.zip -O ~/.pccae32/R_1.zip -nv");
  system("unzip ~/.pccae32/*.zip -d ~/.pccae32/");
  system("rm ~/.pccae32/*.zip");
  FILE *p;
  int ch;

  p = popen("ls ~/.pccae32/", "r");
  if (p == NULL) {
    puts("Unable to open process");
    return (1);
  }
  while ((ch = fgetc(p)) != EOF)
    putchar(ch);
  pclose(p);

  return (0);
}
  */
