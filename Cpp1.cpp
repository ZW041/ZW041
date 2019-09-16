#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct{char c_mkgsegment[20];}customer;
typedef struct
{	int o_orderkey,o_custkey;
	char c_orderdate[20];}order;
typedef struct
{	int l_orderkey;
	float l_extendedprice;
	char l_shipdate[20];}lineitem;
typedef struct
{	int custkey,orderket;
	float price;
	char mkgsegment[20],orderdate[20],shipdate[20];}result;
typedef struct
{	int num;
	char mkgment[20],ship[20],order[20];}find;
customer CUSTOMER[100];
order ORDER[16000];
lineitem LINE[1000];
result RESULT[1000];
find FID[100];
typedef struct
{	int l_order;
	char o_orderda[20];
	float revenue;}last;
int HS_customer()
{  	int i=0,j=0,flag=0;
    char HS_C;
	FILE* fp = NULL;
	fp = fopen("customer.txt", "r+");
	HS_C = getc(fp);
	while (HS_C != EOF)
	{   if (HS_C == '|')
		{	HS_C = getc(fp);
		    flag = 1;}
		if (HS_C == '\n')
		{	i++; HS_C= getc(fp);
		}
		if (flag == 1)
		{   CUSTOMER[i].c_mkgsegment[j] = HS_C;j++;
		}
		HS_C = getc(fp);
	}fclose(fp);
	return 0;
}
int HS_ORDER()
{	FILE* fp = NULL;
	char HS_O;
	int flag = 0;
	int i = 0, j = 0, k = 0, l = 0;
	fp = fopen("orders.txt", "r+");
	HS_O = getc(fp);
	ORDER[i].o_orderkey = 0;
	while (HS_O != EOF)
	{	if (HS_O == '|')
		{	if(flag == 0)flag = 1;
			else 
				if(flag == 1)flag = 2;
			else
				flag = 0;
			HS_O = getc(fp);
		}
		if (HS_O == '\n')
		{	i++; ORDER[i].o_orderkey = 0;HS_O = getc(fp); 
		}
		if (flag == 0)
		{	ORDER[i].o_orderkey = HS_O - '0' + ORDER[i].o_orderkey * 10;
		}
		else if (flag == 1)
		{	int a = 0, b = 0;
			b = a * 10;
			a = HS_O - '0';
			ORDER[i].o_custkey = a + b;
		}
		else if (flag == 2)
		{	ORDER[i].c_orderdate[k]=HS_O;
			k++;
		}
		HS_O = getc(fp);
	}fclose(fp);
	return 0;
}
int HS_LINE()
{
	FILE* fp = NULL;
	char HS_L;
	int flag = 0, i = 0, m = 0, j = 0, k = 1, z = 0;
	fp = fopen("lineitem.txt", "r+");
	LINE[i].l_orderkey = 0;
	HS_L = getc(fp);
	while (HS_L != EOF)
	{   if (HS_L == '|')
		{	if (flag == 0)flag = 1;
			else 
				if (flag == 1)flag = 2;
			else
				flag = 0;
			HS_L = getc(fp);
		}
		if (HS_L == '\n')
		{	i++;LINE[i].l_orderkey = 0;HS_L = getc(fp); 
		}
		if (flag == 0)
		{	LINE[i].l_orderkey = HS_L - '0' + LINE[i].l_orderkey * 10;
		}
		else if (flag == 1)
		{	float IF;
			if (HS_L == '.')
			{	z = 1;HS_L = getc(fp);
			}
			if (z == 0)
			{	IF = HS_L - '0';	LINE[i].l_extendedprice = IF + LINE[i].l_extendedprice * 10;
			}
			else
			{	IF = HS_L - '0';
			for (j = 1; j <= k; j++) {IF = IF * 0.1;}
			LINE[i].l_extendedprice =LINE[i].l_extendedprice + IF;k++;
			}
		}
		else if (flag == 2)
		{	LINE[i].l_shipdate[m]=HS_L;	m++;
		}
		HS_L = getc(fp);
	}fclose(fp);
	return 0;
}
int search(int s)
{	int i;
	for (i = 0; i < 4000; i++)
	{	if (ORDER[i].o_orderkey == s)return i;
		if (ORDER[i].o_orderkey >= s)break;
	}
	return -1;
}
void CULCU()
{	int i, j, z;
	for (i = 0; i < 1000; i++)
	{	j = search(LINE[i].l_orderkey);
		if (j == -1)continue;
		z = ORDER[j].o_custkey;
		if (z == 0)continue;
		RESULT[i].orderket = LINE[i].l_orderkey;
		RESULT[i].custkey = ORDER[j].o_custkey;
		RESULT[i].price = LINE[i].l_extendedprice;
		strcpy(RESULT[i].orderdate,ORDER[j].c_orderdate);
		strcpy(RESULT[i].shipdate,LINE[i].l_shipdate);
		int k;
		for (k = 0; k < 10; k++)
			RESULT[i].mkgsegment[k] = CUSTOMER[z - 1].c_mkgsegment[k];
	}
}
int main()
{
	int i = 0,M1=0,M2=0;
	last falg[1000];
	HS_customer();HS_ORDER();HS_LINE();CULCU();
	int flag;
	scanf("%d", &flag);	
	falg[0].l_order=0;
	for (i = 0; i < flag; i++)
	{	scanf("%s %s %s %d", &FID[i].mkgment, &FID[i].order, &FID[i].ship,&FID[i].num);
	}
	int a,j,z=0;
	for(a=0;a<flag;a++)
	{
	for (i = 0; i < 1000; i++)
	{	for (j = 0; j < 8; j++)
		{if (j == 7)
		{	M1=strcmp(RESULT[i].orderdate,FID[a].order);
			M2=strcmp(RESULT[i].shipdate,FID[a].ship);	
			if(M1<=0&&M2>=0)
			{       if(falg[z].l_order!=RESULT[i].orderket)
					{	z++;
						falg[z].l_order=RESULT[i].orderket;
						strcpy(falg[z].o_orderda,RESULT[i].orderdate);
						falg[z].revenue+=RESULT[i].price;
					}
					else
					{   falg[z].l_order=RESULT[i].orderket;
					    strcpy(falg[z].o_orderda,RESULT[i].orderdate);
				    	falg[z].revenue+=RESULT[i].price;
					}
				}
			}
			if (FID[a].mkgment[j] == RESULT[i].mkgsegment[j])
					continue;
			else break;
		}
	}
	for(i=0;i<=1000;i++)
	{int m,n,k,l;
	float Ma,Mb;
	char Mc[10];
	for(j=i;j<=1000;j++)
	{	m=falg[i].revenue;
		n=falg[j].revenue;
		if(falg[i].l_order>=1000||falg[i].l_order<=0)break;
		if(falg[j].l_order>=1000||falg[j].l_order<=0)break;
			if(m<n)
			{	Ma=falg[j].revenue;Mb=falg[i].revenue;
				falg[j].revenue=Ma;falg[i].revenue=Mb;
				k=falg[i].l_order;l=falg[j].l_order;
				falg[i].l_order=l;falg[j].l_order=k;
				strcpy(Mc,falg[i].o_orderda);
				strcpy(falg[i].o_orderda,falg[j].o_orderda);
				strcpy(falg[j].o_orderda,Mc);}
		}
	}
	printf("l_orderkey|o_orderdate|revenue\n");
	for(i=1;i<=FID[a].num;i++)
	{int o;
	if(falg[i].l_order>=1000||falg[i].l_order<=0)break;
	printf("%d|",falg[i].l_order);
	for(o=0;o<10;o++)
		printf("%c",falg[i].o_orderda[o]);
	printf("|%7.2f",falg[i].revenue);
	}
	}	
	return 0;
}
