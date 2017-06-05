#include "unp.h"

#ifndef MAXSOCKADDR
#define MAXSOCKADDR 128
#endif
int main(int argc,char **argv)
{
	int sockfd,n;
	char revline[MAXLINE+1];
	socklen_t len;
	struct sockaddr  *sa;
	
	if(argc!=3)
	{
		perror("Usage:<host><service>");
		exit(-1);
	}

	sockfd=tcp_connect2(argv[1],argv[2]);
	sa=malloc(MAXSOCKADDR);
	len=MAXSOCKADDR;
	getpeername(sockfd,sa,&len);
//	printf("connect to %s\n",sa->sa_data);
	while((n=read(sockfd,revline, MAXLINE))>0)
	{
		revline[n]=0;
		fputs(revline,stdout);
	}
	exit(0);
}

