#include<stdio.h>
#define MAXN 100
double f(int n,double a[],double x);
int main()
{
    int n,i;
    double  a[MAXN],x;
    scanf("%d %if",&n,&x);
    for(i=0;i<=n;i++)
       scanf("%lf",&a[i]);//一位小数
    printf("%.1f\n",f(n,a,x));
    return 0;
}
double f(int n,double a[],double x)
{
    int i;
    double  b=1.0;
    double  sum=a[0];
    for(i=1;i<=n;i++)
    {
        b=b*x;
        sum=sum+a[i]*b;
    }
    return sum;
}
