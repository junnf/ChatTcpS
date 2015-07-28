#include	"lib/unp.h"

void
str_clii(FILE *fp,char *name ,int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];

  writen(sockfd, name, strlen(name));

	while (fgets(sendline, MAXLINE, fp) != NULL) {

		//writen(sockfd, sendline, 1);
		//sleep(1);
		writen(sockfd, sendline, strlen(sendline));

		if (readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");

		fputs(recvline, stdout);
	}
}
