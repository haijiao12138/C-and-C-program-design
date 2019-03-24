//#include"stdafx.h"
//#include<cstdio.h>
//#include<iostream>

#include <stdio.h>
#include<algorithm>
#include <stdlib.h>
using namespace std;
const int N=1003;
int a[N];
int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0;i<n;i++)
            scanf("%d",a+i);//a[i]
        sort(a,a+n);
        if(n==1)
        {
            printf("%d\n-1\n",a[0]);
            continue;
        }
        bool flag=true;
        printf("%d\n",a[n-1]);
        for(int i=0;i<n-1;i++)
        {
            if(flag)
            {
                flag=false;
                printf("%d ",a[i]);

            }
            else
                printf("%d ",a[i]);
        }
        printf("\n");
    }
    //printf("Hello world!\n");
    return 0;
}














