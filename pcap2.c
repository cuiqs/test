#include "unp.h"
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <pcap/pcap.h>

long int count=0;
static void sig_alrm(int signo)
{
	
	printf("count=:%ld\n",count);
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

//	t1=time(NULL);
//	while(1)
//	{

		packet=pcap_next(descr,&hdr);
		if(packet==NULL)
		{
			printf("Didn't grab packet\n");
			exit(1);
		}
//		count+=hdr.len;
//		t2=time(NULL);
//		if(difftime(t2,t1)>=5)
//		{
//			printf("count=%ld\n",count);
//			t1=t2;
//		}
//	}
	printf("Grabbed packet of length %d\n",hdr.len);
	printf("Recieved at ...%s\n",ctime((const time_t *)&hdr.ts.tv_sec));
	printf("caplen is %d\n",hdr.caplen);

	eptr=(struct ether_header *)packet;
	
	if(ntohs(eptr->ether_type)==ETHERTYPE_IP)
	{
		printf("Ether type hex:%x  dec:%d is a IP packet\n",
				ntohs(eptr->ether_type),
				ntohs(eptr->ether_type));
	}
	else if(ntohs(eptr->ether_type)==ETHERTYPE_ARP)
	{
		printf("Ether type hex:%x  dec:%d is a ARP packet\n",
				ntohs(eptr->ether_type),
				ntohs(eptr->ether_type));
	}
	else
	{
		printf("Ethernet type %x not IP", ntohs(eptr->ether_type));
		exit(1);
	}
		
	exit(0);
	}

