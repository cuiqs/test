#include "unp.h"

int main(int argc,char **argv[])
{
	struct addrinfo  *res;
	char address[256];
	char *pst=address;
	if(argc!=3)
	{
		printf("Usage:hostname service\n");
		exit(1);
	}
	getaddrinfo(argv[1],argv[2],NULL,&res);

	while(res->ai_next!=NULL)
	{
		if(res->ai_canonname!=NULL)
			printf("%s\n",res->ai_canonname);
		inet_ntop(AF_INET,&(((struct sockaddr_in *)(res->ai_addr))->sin_addr),address,sizeof(address));

		printf("address:%s\t",address);
		printf("port:%d\n",((struct sockaddr_in *)res->ai_addr)->sin_port);
		res=res->ai_next;
	}

	return 0;
}

		

