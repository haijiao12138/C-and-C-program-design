//5-1 子集和问题  迭代回溯
#include<stdio.h>
#include<stdlib.h>
#define MAX 10000
int S[MAX] ;
bool v[MAX] ;
int n , c ;
bool traceback(int n){
    int p = 0 ,sum = 0 ;
    while(p>=0)           //开始进行循环操作
    {
       if(v[p]==false)           //如果没有加进S[p]，则加进去，再进行操作
       {
         v[p] = true ;
         sum =sum+ S[p] ;
         if(c == sum)
            return true ;
         else if( c < sum)
          {
           v[p] = false ;
           sum =sum-S[p] ;
          }
          p++ ;             //进行下一个层操作
       }
       if(p>=n)                  //若数字操作进行完全
       {
           while( v[p-1] )      //往上走，再判断
           {
             p-- ;
             v[p] = false ;
             if(p<1)
             return false ;
           }
           while( v[p-1]==false)
           {
            p-- ;
            if(p<1)
            return false ;
           }
           sum=sum-S[p-1] ;
           v[p-1]= false ;
      }
   }
   return false ;
}
  int main()
  {
    scanf("%d %d" , &n , &c) ;
    for(int i = 0 ; i < n ; i++)
       scanf("%d" , &S[i]) ;
    if(traceback(n))     //若返回为真
    {
      for(int i = 0 ; i < n; i++)
         if(v[i])
         {
           printf("%d" ,S[i]) ;
           printf(" ") ;
         }
      printf("\n") ;
   }
   else
    printf("No Solution!\n") ;
    system("pause");
    return 0 ;
}
