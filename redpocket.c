#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void redpocket(int total,int *p,int n)
{
	int aver=total/n;
	int i,j;
	int takemoney,win;
	
	for(i=0;i<n-1;i++)
	{
		*(p+i)=aver;
	}
	*(p+n-1)=total-aver*(n-1);
	srand((unsigned int)time(NULL));
	for(i=0;i<n;i++)
	{
		takemoney=rand()%*(p+i);
		win=rand()%n;
		*(p+i)-=takemoney;
		*(p+win)+=takemoney;
	}

	return;
}

int main(void)
{
	float totalmoney;
	int pocket,money,i;
	int *p;

	scanf("%f",&totalmoney);
	scanf("%d",&pocket);
	money=(int)(totalmoney*100);
	p=(int *)malloc(sizeof(int)*pocket);
	redpocket(money,p,pocket);
	for(i=0;i<pocket;i++)
	 	printf("%d fen\n",*(p+i));

	return 0;
}

