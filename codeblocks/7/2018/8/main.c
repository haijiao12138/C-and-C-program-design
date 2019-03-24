#include<stdio.h>
int main()
{
    int n,u,d;
    int b;
    scanf("%d %d %d",&n,&u,&d);
    b=(n-2)/(u-d);
    printf("%d",b*2+1);
    return 0;
}
