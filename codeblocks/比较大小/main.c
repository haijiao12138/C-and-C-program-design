#include<stdio.h>
#include<stdlib.h>
int main()
{
  int a,b,c;
  int t1,t2,t3;
  scanf("%d%d%d",&a,&b,&c);
  if(a>b)
     {
       if(a>c)
          {
            t1=a;
            if(b>c)
              {t2=b;
              t3=c;
              }
            else
            {
            t2=c;
             t3=b;
            }
          }
       else//a<c
         {
           t1=c;
           t2=a;
           t3=b;
         }
     }
  else//b>a
  {
    if(b>c)
       {
         t1=b;
       if(a>c)
         { t2=a;t3=c;}
        else
          { t2=c;t3=a;}
       }
    else//c>b
     {
       t1=c;
     t2=b;
     t3=a;

     }

  }
  printf("%d->%d->%d",t3,t2,t1);
  return 0;
}
