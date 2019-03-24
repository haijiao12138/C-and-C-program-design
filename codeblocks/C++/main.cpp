#include <iostream>
#include<algorithm>
using namespace std;
int n;

 int minsum(int a[],int m)//表示数组中序列的长度和序列的个数
 {
     int b[n];
     int sum=0;
     int i;
     for(i=0;i<n;i++)
     {
         b[i]=a[i];
     }
     while(m>1)
     {
         int i;
         sort(b,b+m);
         b[0]=b[0]+b[1];
         sum=sum+b[0];
         for(i=1;i<m-1;i++)
         {
             b[i]=b[i+1];
         }
         m--;
     }
     return sum-n+1;//sum-（n-1）
 }
 int maxsum(int a[],int m)
 {
     int i;
     int b[n];
     int c[n];
     int sum=0;
     int l;
     for(i=0;i<n;i++)
     {
         b[i]=a[i];
     }
     sort(b,b+m);

     l=m-1;
     int j=0;
     for(i=l;i>=0;i--)
     {
         c[j]=b[i];
         j++;
     }
     while(m>1)
     {
         //j=j-1;
         c[0]=c[0]+c[1];
         sum=sum+c[0];
         for(i=1;i<m-1;i++)
         {
             c[i]=c[i+1];
         }
         m--;

     }
     return sum-n+1;

 }
int main()
{
    int a[100];
   cin>>n;
   int i;
   for(i=0;i<n;i++)
   {
       cin>>a[i];
   }
   cout<<minsum(a,n);
   cout<<endl;
   cout<<maxsum(a,n);
    return 0;
}
