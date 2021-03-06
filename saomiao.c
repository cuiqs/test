#include "unp.h"

void sig_chld(int signo)
{
	pid_t pid;
	int stat;
	
	while((pid=waitpid(-1,&stat,WNOHANG))>0)
	{
		printf("the child %d terminated\n",pid);
	}
	return;
}

void num_add(int sockfd)
{
	long n1,n2;
	char line[MAXLINE];
	ssize_t n;

	while(1)
	{
		if((n=read(sockfd,line,MAXLINE))==0)
			return;
		if((sscanf(line,"%ld%ld",&n1,&n2))==2)
			snprintf(line,sizeof(line),"%ld\n",n1+n2);
		else
			snprintf(line,sizeof(line),"input error\n");
		write(sockfd,line,strlen(line));
	}
}
				
void str_echo(int sockfd)
{
	char line[MAXLINE];
	ssize_t n;

	while(1)
	{
		if((n=read(sockfd,line,MAXLINE))==0)
			return ;
		write(sockfd,line,n);
	}
}

int main(int argc,char **argv)
{
	int listenfd,connfd,i;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;

	for(i=1;i<65535;i++)
	{
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(i);
	if(bind(listenfd,(SA *)&servaddr,sizeof(servaddr))==-1)
	{
		if(errno==EADDRINUSE||errno==EINVAL)
			printf("the port %d is inuse\n",i);
	}
	}

}
