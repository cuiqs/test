#include "unp.h"
#include <sys/utsname.h>

char **my_addrs(int *addrtype)
{
	struct hostent *hptr;
	struct utsname myname;
	if(uname(&myname)<0)
		return NULL;
	if((hptr=gethostbyname(myname.nodename))==NULL)
		return NULL;
	*addrtype=hptr->h_addrtype;
	return hptr->h_addr_list;
}

int main(int argc,char **argv)
{
	int addr_type;
	char **result;

	char buf[INET6_ADDRSTRLEN];

	result=my_addrs(&addr_type);
	while(*result!=NULL)
		printf("%s\n",inet_ntop(addr_type,*result++,buf,sizeof(buf)));
}
				
