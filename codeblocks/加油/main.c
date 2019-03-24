#include <stdio.h>
#include <stdlib.h>
int a[100];
int count=0;
void Count(int max1,int n)
{
    int i,j;
    int unreach=0;
    for(i=0;i<=n;i++)
    {
        scanf("%d",&a[i]);
        if(a[i]>max1)
            unreach=1;
    }
    if(unreach==1)
    {
        printf("No Solution!");
    }
    else
    {
        int max=0;
        for(j=0;j<=n;j++)
        {
            max=max+a[j];
            if(max>max1)
            {
                j--;
                max=0;
                count++;
            }
        }
        printf("%d\n",count);
    }

}
int main()
{
    int n;
    int max1;
    scanf("%d%d",&max1,&n);//距离和加油站个数
    //输出
    Count(max1,n);


    return 0;
}


















