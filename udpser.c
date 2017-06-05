#include "unp.h"


void dg_echo(int sockfd, SA *cliaddr,socklen_t clilen)
{
	int n;
	socklen_t len;
	char mesg[MAXLINE];

	for( ; ; )
	{
		len=clilen;
		n=recvfrom(sockfd,mesg,MAXLINE,0,cliaddr,&len);
		sendto(sockfd,mesg,n,0,cliaddr,len);
	}
}

void dg_echo2(int sockfd, SA *cliaddr,socklen_t clilen)
{
	int n,count;
	socklen_t len;
	char mesg[MAXLINE];

	for( ; ; )
	{
		len=clilen;
		n=recvfrom(sockfd,mesg,MAXLINE,0,cliaddr,&len);
		printf("count: %d\n",count++);
	}
}

int main(int argc,char **argv)
{
	int sockfd;
	struct sockaddr_in seraddr,cliaddr;

	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	bzero(&seraddr,sizeof(seraddr));
	seraddr.sin_family=AF_INET;
	seraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	seraddr.sin_port=htons(SERV_PORT);

	bind(sockfd,(SA *)&seraddr,sizeof(seraddr));
	dg_echo2(sockfd,(SA *)&cliaddr,sizeof(cliaddr));
}

