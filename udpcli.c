#include "unp.h"


void dg_cli(FILE *fp,int fd,const SA *pseraddr,socklen_t servlen)
{
	int n;
	char line[MAXLINE],revline[MAXLINE];

	while((fgets(line,MAXLINE,fp))!=NULL)
	{
		sendto(fd,line,strlen(line),0,pseraddr,servlen);
		memset(line,'\0',MAXLINE);
		n=recvfrom(fd,revline,MAXLINE,0,NULL,NULL);
		revline[n]=0;
		fputs(revline,stdout);
	}
}
void dg_cli2(FILE *fp,int fd,const SA *pseraddr,socklen_t servlen)
{
	int n;
	char line[MAXLINE],revline[MAXLINE];
	SA sa;
	sa.sa_family=AF_UNSPEC;
	connect(fd,(SA *)pseraddr,servlen);

	while((fgets(line,MAXLINE,fp))!=NULL)
	{
		write(fd,line,strlen(line));
		memset(line,'\0',MAXLINE);
		n=read(fd,revline,MAXLINE);
		revline[n]=0;
		fputs(revline,stdout);
	//	sa.sa_family=AF_UNSPEC;
	//	connect(fd,&sa,sizeof(sa));
	}
}
void dg_cli3(FILE *fp,int fd,const SA *pseraddr,socklen_t servlen)
{
	int n;
	char line[MAXLINE],revline[MAXLINE];

	for(int i=0;i<2000;i++)
	{
		sendto(fd,line,1400,0,pseraddr,servlen);
	}
}
int main(int argc,char **argv)
{
	int sockfd;
	struct sockaddr_in seraddr;

	if(argc!=2) 
	{
		printf("usage:udpcli <ip address>\n");
		exit(1);
	}

	bzero(&seraddr,sizeof(seraddr));
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(SERV_PORT);
	inet_pton(AF_INET,argv[1],&seraddr.sin_addr);

	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	dg_cli3(stdin,sockfd,(SA *)&seraddr,sizeof(seraddr));
	exit(0);
}
