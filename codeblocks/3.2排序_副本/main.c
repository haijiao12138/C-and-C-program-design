#include <stdio.h>
#include <stdlib.h>

int main()
{
   int n;
 int buf[100];//����һ���㹻������飬�����洢Ҫ ���������
 int i,j;
 int temp;
 scanf("%d",&n);

    for(i=0;i<n;i++)
	{
	  scanf("%d",&buf[i]);
	}


 //����������Ԫ��
     for(i=0;i<n;i++)
      {
       for(j=0;j<n-1-i;j++)
	     {
	       if(buf[j]>buf[j+1])
	         temp=buf[j];
	         buf[j]=buf[j+1];
	         buf[j+1]=temp;
	     }
       }//ð��ѭ�����壬ÿ��ѭ�������������ŵ�����λ�ã�
     for(i=0;i<n;i++)
       { printf("%d ",buf[i]);}//ÿ��ѭ����ɺ󶼻���Ԫ�غ����һ���ո�
     printf("\n");//������У�

return 0;
}
