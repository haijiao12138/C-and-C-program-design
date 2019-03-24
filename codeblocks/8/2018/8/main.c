#include<stdio.h>
int main()
{
    int x,y,n;
    int i;
    int j;
    int count=1;
    scanf("%d",&n);
    for(i=1;i<=100;i++)
    {
        for(j=1;j<100;j++)
        {
            if(i*i+j*j==n&&i<j)
              {
                  count++;
                  printf("%d %d",i,j);
                  printf("\n");
              }
        }
    }
    if(count==1)
     printf("No Solution");
    return 0;
}
