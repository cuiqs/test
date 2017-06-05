#include "unp.h"


void str_cli(FILE *fp,int sockfd)
{
	char revline[MAXLINE];
	char sendline[MAXLINE];

	while(fgets(sendline,MAXLINE,fp)!=NULL)
	{
		write(sockfd,sendline,strlen(sendline));
		memset(revline,'\0',MAXLINE);
		if((read(sockfd,revline,MAXLINE))==0)
		{
			perror("recieve error\n");
			exit(0);
		}
		fputs(revline,stdout);

	}
	return;
}


void str_cli2(FILE *fp,int sockfd)
{
	char revline[MAXLINE];
	char sendline[MAXLINE];
	int maxfd1;
	int stdineof;
	fd_set rset;

	FD_ZERO(&rset);
	stdineof=0;
	for(; ;)
	{
		if(stdineof==0)
			FD_SET(fileno(fp),&rset);
		FD_SET(sockfd,&rset);
		maxfd1=max(fileno(fp),sockfd)+1;
		select(maxfd1,&rset,NULL,NULL,NULL);
		
		if(FD_ISSET(sockfd,&rset))
		{
			if((read(sockfd,revline,MAXLINE))==0)
			{
				if(stdineof==1)
					return;
				else
					exit(EXIT_FAILURE);
			}
			fputs(revline,stdout);
			memset(revline,'\0',MAXLINE);
		}
		
		if(FD_ISSET(fileno(fp),&rset))
		{
			if((fgets(sendline,MAXLINE,fp))==NULL)
			{
				stdineof=1;
				shutdown(sockfd,SHUT_WR);
				FD_CLR(fileno(fp),&rset);
				continue ;
			}
			write(sockfd,sendline,strlen(sendline));
		}
	}
}

	
int main(int argc,char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;

	if(argc!=2)
	{
		perror("need server address\n");
		exit(0);
	}

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(9999);
	inet_pton(AF_INET,argv[1],&servaddr.sin_addr);

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	connect(sockfd,(SA *)&servaddr,sizeof(servaddr));

	str_cli(stdin,sockfd);
//	str_cli2(stdin,sockfd);
	exit(0);

}



