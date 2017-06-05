#include "unp.h"

int main()
{
	char ca[256];
	char *ps=ca;
	ps=gai_strerror(EAI_AGAIN);
		
	printf("%s\n",ps);
	return 0;
}
