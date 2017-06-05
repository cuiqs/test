#include "unp.h"
#include <time.h>

int main(int argc, char **argv)
{
	int listenfd,connfd;
	socklen_t addrlen,len;

	char buf[MAXLINE];
	time_t tick;

	struct sockaddr *cliaddr;

	if(argc!=2)
	{
		perror("Usage:daytime <port>");
		exit(-2);
	}
	listenfd=tcp_listen2(NULL,argv[1],&addrlen);
	cliaddr=malloc(addrlen);
	for(; ;)
	{
		len=addrlen;
		connfd=accept(listenfd,cliaddr,&len);
		//printf("connect from %s\n",cliaddr->sa_data);
		tick=time(NULL);
		snprintf(buf,sizeof(buf),"%.24s\r\n",ctime(&tick));
		write(connfd,buf,strlen(buf));
		close(connfd);
	}
}

