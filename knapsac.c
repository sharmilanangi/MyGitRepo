#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{
	int idx;
	int w;
	int v;
	float comp;
}node;

void swap(node *a,node *B);
void SORT(node *ND,int n);
int OPTIMAL(node *ND,int n,int B,int **V,int *COUNT);
int OPTIMAL1(node *ND,int n,int B,int **V,int **S,int *COUNT);
void PRINT(int **S,node *ND,int **V,int n,int B,int* COUNT);

//**************************************************CHANGE************************************//

void main()
{
	int n,B,i,j,x;
	node *ND;
	int **V,**S;
	int *COUNT;
	printf("give the value of n\n");
	scanf("%d",&n);
	printf("give the value of max weight B\n");
	scanf("%d",&B);
	ND=(node *)malloc((n+1) * sizeof(node));
	V=(int **)malloc((n+1)*sizeof(int *));
	COUNT=(int *)malloc((n+1)*sizeof(int));
	S=(int **)malloc((n+1)*sizeof(int *));
	for(i=0;i<=n;i++)
		{
			V[i]=(int *)malloc((B+1)*sizeof(int));
		}
	for(i=0;i<=n;i++)
		{
			S[i]=(int *)malloc((B+1)*sizeof(int));
		}
	
	printf("give the values of weights\n");

	for(i=1;i<=n;i++)
	{
		ND[i].idx=i;
	}
	
	for(i=1;i<=n;i++)
		{
			scanf("%d",&ND[i].w);
		}
	printf("give the values of costs\n");
	for(i=1;i<=n;i++)
		{
			scanf("%d",&ND[i].v);
		}
	for(i=1;i<=n;i++)
	{
		ND[i].comp=((float)ND[i].v)/((float)ND[i].w);
	}
	//SORT(ND,n);
	for(i=1;i<=n;i++)
		{
			printf("%d  ",ND[i].w);
		}
	printf("\n");
	x=OPTIMAL(ND,n,B,V,COUNT);
	printf("%d\n",x);
	printf("counts\n");
	for(i=1;i<=n;i++)
		{
			printf("%d   ",COUNT[i]);
		}
	printf("\n");

	x=OPTIMAL1(ND,n,B,V,S,COUNT);
	printf("%d\n",x);

/*	for(i=1;i<=n;i++)
		{
			for(j=1;j<=B;j++)
				{
					printf("%d  ",V[i][j]);
				}
			printf("\n");
		}
	printf("\n");
*/
	//PRINT(S,ND,V,n,B,COUNT);

}

void swap(node *a,node *b)
{
	node temp;
	temp.idx=(*a).idx;
	temp.w=(*a).w;
	temp.v=(*a).v;
	temp.comp=(*a).comp;
	(*a).idx=(*b).idx;
	(*a).w=(*b).w;
	(*a).v=(*b).v;
	(*a).comp=(*b).comp;
	(*b).idx=temp.idx;
	(*b).w=temp.w;
	(*b).v=temp.v;
	(*b).comp=temp.comp;
}

	
void SORT(node *ND,int n)
{
	int i,j;
	for(i=n;i>=1;i--)
		{
			for(j=1;j<i;j++)
				{
					if(ND[j].comp>ND[j+1].comp)
					swap(&ND[j],&ND[j+1]);
				}
		}
}

//USING TOP - DOWN PROCEDURE

int OPTIMAL(node *ND,int n,int B,int **V,int *COUNT)
{
	int i,j,k,temp,q;
	if(n<=0 || B<=0)
		{
			return 0;
		}
		
	if(ND[n].w>B)	
		{
			 COUNT[ND[n].idx]=0;			
			 return OPTIMAL(ND,n-1,B,V,COUNT);
		}
	
	else
	{
		temp=B/(ND[n].w);
		q=-1000;
		for(i=0;i<=temp;i++)
		{
			
			k=i*(ND[n].v)+OPTIMAL(ND,n-1,B-(i*(ND[n].w)),V,COUNT);
			if(k>q)
			{
				q=k;
				COUNT[ND[n].idx]=i;
				
			}
		}
		return k;
	}


}

// USING BOTTOM TO UP

int OPTIMAL1(node *ND,int n,int B,int **V,int **S,int *COUNT)
{
	int i,j,l,k,flag=0,max,temp;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=B;j++)
			{
				if(i==1 || j==1)	
					{
						V[i][j]=0;
						S[i][j]=0;
					}
				else if(ND[i].w<=B)
				{
					temp=B/(ND[n].w);
					max=-100000;
					for(l=0;l<=temp;l++)
						{
							if(j-(l*ND[n].w) < 1)	break;
							else
							{
								k=l*(ND[n].v)+V[i-1][j-(l*ND[n].w)];
								if(k>max)
								{
									max=k;
									V[i][j]=max;
									S[i][j]=l;
								}		
								
							}
						}
				}
				else
				{
					V[i][j]=V[i-1][j];
					S[i][j]=0;
				}
			}
	}

return V[n][B];
}

void PRINT(int **S,node *ND,int **V,int n,int B,int* COUNT)
{
	int i,j,l;
	i=n;
	j=B;
	if(B<1)	return ;
	for(i=n;i>=1;i--)
		{
			COUNT[i]=S[i][j];
			l=S[i][j];	
			j=j-l*ND[i].w;
		}
	
	for(i=1;i<=n;i++)
		{
			printf("%d   ",COUNT[i]);
		}
	printf("\n");

}

