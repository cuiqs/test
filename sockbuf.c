#include "unp.h"

int main(int argc,char **argv)
{
	int tcpfd,udpfd,len,val;

	tcpfd=socket(AF_INET,SOCK_STREAM,0);
	udpfd=socket(AF_INET,SOCK_DGRAM,0);
        len=sizeof(int);
	if((getsockopt(tcpfd,SOL_SOCKET,SO_RCVBUF,&val,&len))==-1)
	{
		perror("getsockopt error");
	}
	else
		printf("tcp recieve buffer is %d\n",val);

	if((getsockopt(tcpfd,SOL_SOCKET,SO_SNDBUF,&val,&len))==-1)
	{
		perror("getsockopt error");
	}
	else
		printf("tcp send buffer is %d\n",val);

	if((getsockopt(udpfd,SOL_SOCKET,SO_RCVBUF,&val,&len))==-1)
	{
		perror("getsockopt error");
	}
	else
		printf("udp recieve buffer is %d\n",val);

			
	if((getsockopt(udpfd,SOL_SOCKET,SO_SNDBUF,&val,&len))==-1)
	{
		perror("getsockopt error");
	}
	else
		printf("udp send buffer is %d\n",len);

}			
