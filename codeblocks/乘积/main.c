#include<stdio.h>
int BEST(int n)
{
    int max=0;
    int r;
    int i;
    if(n==1)
        printf("1");
    else if(n==2)
        printf("2");
    else if(n==3)
        printf("3");
    else
    {
        int smallmax=0;
    for( i=n-1;i>1;i--)
    {
        r=i*BEST(n-i);
        printf("%d",r);
        if(r>smallmax)
            smallmax=r;
    }
    max=smallmax;
    }
    printf("%d",max);

}
int main()
{
    int max=0;

    printf("the number is:");
        max=BEST(5);




}
