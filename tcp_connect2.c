#include "unp.h"

int tcp_connect2(char *host,char *serv)
{
	int sockfd,n;
	struct addrinfo  hint,*res,*ressave;

	bzero(&hint,sizeof(struct addrinfo));
	hint.ai_family=AF_UNSPEC;
	hint.ai_socktype=SOCK_STREAM;

	if((getaddrinfo(host,serv,&hint,&res))!=0)
	{
		perror("tcp_connect error ");

		exit(-1);
	}
	ressave=res;
	do
	{
		sockfd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
		if(sockfd<0)
			continue;
		if(connect(sockfd,res->ai_addr,res->ai_addrlen)==0)
			break;
		close(sockfd);
	}while((res=res->ai_next)!=NULL);

	if(res==NULL)
	{
		perror("can not connect");
		exit(-2);
	}

	freeaddrinfo(ressave);

	return(sockfd);
}

int tcp_listen2(char *host,const char *serv,socklen_t *addrlenp)
{
	int listenfd,n;
	const int on=1;
	struct addrinfo hints,*res,*ressave;

	bzero(&hints,sizeof(struct addrinfo));
	hints.ai_flags=AI_PASSIVE;
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;

	if((n=getaddrinfo(host,serv,&hints,&res)!=0))
	{
		perror("getaddrinfo error!");
		exit(-2);
	}

	ressave=res;

	do
	{
		listenfd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
		if(listenfd<0)
			continue;
		setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
		if( bind(listenfd,res->ai_addr,res->ai_addrlen)==0)
			break;
		close(listenfd);
	}while((res=res->ai_next)!=NULL);
 	if(res==NULL)
	{
		perror("tcp listen error");
		exit(-3);
	}

	listen(listenfd,LISTENQ);
	if(addrlenp)
		*addrlenp=res->ai_addrlen;
	freeaddrinfo(ressave);
	return(listenfd);
}
