#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pcap/pcap.h>

int main(int argc,char **argv)
{
	char *dev,errbuf[PCAP_ERRBUF_SIZE];
	dev=pcap_lookupdev(errbuf);
	if(dev==NULL)
		printf("error:%s\n",errbuf);
	else
		printf("device :%s\n",dev);
	return 0;
}
