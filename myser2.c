#include "unp.h"

int main(int argc,char **argv)
{
	int i,maxi,maxfd,listenfd,connfd,sockfd;
	char revline[MAXLINE], sendline[MAXLINE];
	int nready,client[FD_SETSIZE];
	ssize_t n;
	socklen_t clilen;
	struct sockaddr_in servaddr,cliaddr;
	fd_set rset,allset;

	listenfd=socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(SERV_PORT);
	bind(listenfd,(SA*)&servaddr,sizeof(servaddr));
	listen(listenfd,LISTENQ);

	for(i=0;i<FD_SETSIZE;i++)
		client[i]=-1;
	maxfd=listenfd;
	maxi=-1;

	FD_ZERO(&allset);
	FD_SET(listenfd,&allset);
	
	for(; ;)
	{
		rset=allset;
		nready=select(maxfd+1,&rset,NULL,NULL,NULL);
		if(FD_ISSET(listenfd,&rset))
		{
			clilen=sizeof(cliaddr);
			connfd=accept(listenfd,(SA *)&cliaddr,&clilen);
			for(i=0;i<FD_SETSIZE;i++)
			{
				if(client[i]==-1)
				{
					client[i]=connfd;
					break;
				}
			}
			if(maxi<i)
				maxi=i;
			printf("maxi:%d\n",maxi);
			if(i==FD_SETSIZE)
				exit(EXIT_FAILURE);
			FD_SET(connfd,&allset);
			if(connfd>maxfd)
				maxfd=connfd;
			if(--nready<=0)
				continue;
		}
		for(i=0;i<FD_SETSIZE;i++)
		{
			if((sockfd=client[i])<0)
				continue;
			if(FD_ISSET(sockfd,&rset))
			{
				if((n=read(sockfd,revline,MAXLINE))==0)
				{
					close(sockfd);
					client[i]=-1;
					FD_CLR(sockfd,&allset);
				}
				else
					write(sockfd,revline,n);
				memset(revline,'\0',MAXLINE); 

			if(--nready<=0)
				break;
			}
		}
	}
}
