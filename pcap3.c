#include "unp.h"
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <pcap/pcap.h>

long int count=0;
static void sig_alrm(int signo)
{
	
	printf("count=:%ld\n",count);

}


void my_callback(unsigned char *useless,const struct pcap_pkthdr *hdr,const unsigned char *packet)
{
	static long total=0;
	static int count=0;
	count++;
	total+=hdr->len;

	if(count%100==0)
		fprintf(stdout,"count=%d\ttotal=%ld\n",count,total);
	fflush(stdout);
}

int main(int argc,char *argv[])
{
	int i;
	char *dev;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *descr;
	const u_char *packet;
	struct pcap_pkthdr hdr;
	struct ether_header *eptr;
	time_t t1,t2;
	u_char *ptr;

	dev=pcap_lookupdev(errbuf);
	if(dev==NULL)
	{
		printf("%s\n",errbuf);
		exit(1);
	}
	printf("DEV:%s\n",dev);

	descr=pcap_open_live(dev,BUFSIZ,0,0,errbuf);
	if(descr==NULL)
	{
		printf("pcap_open_live():%s\n",errbuf);
		exit(1);
	}
	
	pcap_loop(descr,-1,my_callback,NULL);

	
		
	exit(0);
	}

