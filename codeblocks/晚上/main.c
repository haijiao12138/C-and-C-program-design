#include<stdio.h>
#define N 101
void main()
{
    int i;
int a[N]={0}, s,e,k,max;
scanf("%d",&k);
for( i=1;i<=k;i++)
{
scanf("%d%d",&s,&e);
for(;s<=e;s++)
a[s]++;
}
max=a[1];
for( i=2;i<=N;i++)
if(max<a[i])max=a[i];
printf("%d",max);
}
