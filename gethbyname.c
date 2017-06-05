#include "unp.h"

int main(int argc,char **argv)
{
	char *ptr,**pptr;
	char str[INET6_ADDRSTRLEN];
	struct hostent *hptr;

	while(--argc>0)
	{
		ptr=*++argv;
	//	if((hptr=gethostbyname(ptr))==NULL)

		if((hptr=gethostbyname2(ptr,AF_INET6))==NULL)
		{
			perror("no this host");
			continue;
		}
		printf("offcial hostname:%s\n",hptr->h_name);
		for(pptr=hptr->h_aliases;*pptr!=NULL;pptr++)
		{
			printf("aliases:%s\n",*pptr);
		}

		switch(hptr->h_addrtype)
		{
			case AF_INET:
			#ifdef AF_INET6
			case AF_INET6:
			#endif
				pptr=hptr->h_addr_list;
				for(;*pptr!=NULL;pptr++)
					printf("address:%s\n",inet_ntop(hptr->h_addrtype,*pptr,str,sizeof(str)));
				break;
			default:
				perror("addrtype error");
				return 2;
				break;
		}
	}
	exit(0);
}
