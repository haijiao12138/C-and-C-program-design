#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n,k;
    int i;
    int j;
    int i1;
    scanf("%d%d",&n,&k);
    int a[100];
    int temp;
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(i1=0;i1<k;i1++)
    {
        for(i=0,j=i+1;j<n-i1;j++,i++)
        {
            if(a[i]>a[j])
            {
                temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }

    }
    for(i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}
