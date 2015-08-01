#include<stdio.h>
char _buffer[256][256];
char (*_p_buff)[256] = _buffer;
//int enqueue(char (*mesg)[256]);
void ttt(char mesg[][256]){
    mesg = "aaaaa";
    printf("%s\n",mesg);
    mesg++ ;
    mesg = "bbbbb";
    printf("%s\n",mesg);
    mesg++;
    mesg = "cccccccccccc";
    printf("%s\n",mesg);
    printf("%c",*(*(mesg+0)+1));
    //mesg++; 
    //printf("%d",mesg);
    //char **_p = mesg+1;
    //_p = "xxxxx";
   // printf("%s",mesg);
   // mesg--;
   // printf("%s",mesg);
    // printf("\n%s",*(mesg+1));
   // printf("%c", _p[0]);
}
int main(void) {
  //*_p_buff = "aaaaaa";
  ttt(_p_buff);
 // printf("%d %d %d",_buffer,_buffer+1, _buffer+2);
  //printf("%s",*_p_buff);
  
}
