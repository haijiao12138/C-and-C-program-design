/*#include<stdio.h>
#define N 101
void main()
{
    printf("ÇëÊäÈë×éÊı£º");
    int n;
    int i;
   scanf("%d",&n);
    int a[n];
    int b[n];
    for(i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
     for(i=1;i<=n;i++)
    {
        scanf("%d",&b[i]);
    }
    int p=1;
    int j=1;
    for(i=2;i<=n;i++)
    {
        if(a[i]>=b[j])
        {
            p++;
            j=i;

        }
        else
            p=p;
    }
    printf("%d",p);
*/
#include<stdio.h>
#define N 101
int main()
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



