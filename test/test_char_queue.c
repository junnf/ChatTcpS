#include<stdio.h>
int main(){
  char a[10][10];
  static char b[2][10];
  *b[0]="aaaaaaaaa";
  *b[1]="bbbb";
  char *c = b;
  printf("%s",c);
  return 0;
}
