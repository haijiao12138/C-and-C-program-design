//5-1 �Ӽ�������  ��������
#include<stdio.h>
#include<stdlib.h>
#define MAX 10000
int S[MAX] ;
bool v[MAX] ;
int n , c ;
bool traceback(int n){
    int p = 0 ,sum = 0 ;
    while(p>=0)           //��ʼ����ѭ������
    {
       if(v[p]==false)           //���û�мӽ�S[p]����ӽ�ȥ���ٽ��в���
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
          p++ ;             //������һ�������
       }
       if(p>=n)                  //�����ֲ���������ȫ
       {
           while( v[p-1] )      //�����ߣ����ж�
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
    if(traceback(n))     //������Ϊ��
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
