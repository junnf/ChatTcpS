#include	"lib/unp.h"
#include  "error.h"
#include  "writen.h"
#include  "str_cli11.h"
#include  "readline.h"


int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;
  char *user = NULL;
	if (argc != 2)
		err_quit("usage: tcpcli <IPaddress>");
  //user = argv[2];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9999);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
	str_clii(stdin, sockfd);		/* do it all */
	exit(0);
}
