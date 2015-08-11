#include  "lib/unp.h"
#include  "error.h"
#include "writen.h"
#include <unistd.h>

//static char _user[50];
//char *_u_pointer = _user;
void _str_echo(int sockfd);
void deal_sockset_echo(int *fd_sockset, int sockfd);
/*
  [1]some message
  [2]some message
  ...
  ...
   */

/*char mesg[128][128];
char (*p_mesg_user1)[256] = mesg;
char (*p_mesg_user2)[256] = mesg;
*/

//two person Chat-
//
//int Socket(int family, int type, int protocol);
//void Listen(int fd, int backlog);

int main(int argc,char **argv){

/*
  _connfd  as already finish 3-times-handshake Connection-Socket-F-Description 
  (Value-Result Parameter):cliaddr,clilen
 */

    int _sockfd;
    int _connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;
    //zero mem
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    _sockfd = socket(AF_INET, SOCK_STREAM ,0);

    //INADDR_ANY Handle poly-interface condition
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(9999);
    bind(_sockfd, (SA *) &servaddr, sizeof(servaddr));
    //LISTENQ define maxium connections(in unp.h)
    listen(_sockfd,LISTENQ);
    //1  p:read c:write
    //2 p:write c:read
    int pipe_1[2];
    int pipe_2[2];
    if(pipe(pipe_1) < 0 ){
        perror("pipe");
        exit(1);
    }
    if(pipe(pipe_2) < 0){
        perror("pipe");
        exit(1);
    }

    for(;;){    
        clilen = sizeof(cliaddr);
        _connfd = accept(_sockfd, (SA *)&cliaddr, &clilen);
         if((childpid = fork()) == 0){
          if(childpid > 0 ){
              
          }else{
              
          }
          close(_sockfd);
          //str_echo(_connfd);
          exit(0);
         }
        close(_connfd);
    }

    return 0;
}

int Socket(int family, int type, int protocol){
    int n;
    if((n=socket(family,type,protocol))<0){
        err_sys("socket error");
    }
    return(n);
}

void deal_sockset_echo(int *fd_sockset, int sockfd){
  ssize_t n;
  short _sock_count = 0;
  char buf[MAXLINE];
again_ :
    while((n = read(sockfd,buf,MAXLINE )) > 0){
        
       /*//user-name
       writen(sockfd, user, strlen(user));
       */
      for(;_sock_count>0;_sock_count++){
          writen( fd_sockset[_sock_count], buf, n );
      }
      //
      _sock_count = 0;
    }
    if (n<0 && errno == EINTR){
        goto again_;
    }
    else if (n < 0){
        err_sys("read error");
    }
}


//echo string
void _str_echo(int sockfd){
    ssize_t n;
    short i_user_judge = 0;
    char buf[MAXLINE];
    char user[25];
    char nde[3] = ":";
again:
    while((n=read(sockfd,buf,MAXLINE)) > 0){
        if(i_user_judge == 0){
            i_user_judge = 1;
            bcopy(buf, user, strlen(buf));
            memcpy(_user, buf, strlen(buf));
            _u_pointer = _u_pointer + strlen(buf);
            strcat(user,nde);
            bzero(buf,MAXLINE);
        }
        //strcat(user,nde);
        writen(sockfd, user, strlen(user));
        writen(sockfd, buf, n);
        //bzero(sockfd,MAXLINE);
        //writen(sockfd, buf, n);
        //printf("%s",buf);
    }
    if (n<0 && errno == EINTR)
        goto again;
    else if (n < 0){
        err_sys("read error");
    }
}
//!---   LISTENQ MAXIUM
//void 
//Listen(int fd, int backlog){
//    char *ptr;
//
//}
