#include <stdio.h>
#include <stdlib.h>

int main()
{
   int n;
 int buf[100];//定义一个足够大的数组，用来存储要 排序的数组
 int i,j;
 int temp;
 scanf("%d",&n);

    for(i=0;i<n;i++)
	{
	  scanf("%d",&buf[i]);
	}


 //输入待排序的元素
     for(i=0;i<n;i++)
      {
       for(j=0;j<n-1-i;j++)
	     {
	       if(buf[j]>buf[j+1])
	         temp=buf[j];
	         buf[j]=buf[j+1];
	         buf[j+1]=temp;
	     }
       }//冒泡循环主体，每次循环都将最大的数放到最后的位置，
     for(i=0;i<n;i++)
       { printf("%d ",buf[i]);}//每次循环完成后都会在元素后面加一个空格
     printf("\n");//输出换行，

return 0;
}
