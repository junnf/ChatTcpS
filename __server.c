#include  "lib/unp.h"
#include  "error.h"
#include "writen.h"
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
    for(;;){
        clilen = sizeof(cliaddr);
        _connfd = accept(_sockfd, (SA *)&cliaddr, &clilen); 
          str_echo(_connfd);
          
        
       // close(_connfd);
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

//echo string
void str_echo(int sockfd){
    ssize_t n;
    char buf[MAXLINE];
again:
    while((n=read(sockfd,buf,MAXLINE)) > 0){
        writen(sockfd, buf, n);
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
