 #include<stdio.h>
 int main()
 {
 int n;
 int buf[100];//����һ���㹻������飬�����洢Ҫ ���������
 int i,j;
 int a,b,c;
 int temp;
 while(scanf("%d",&n)!=EOF)
 {
    for( i=0;i<n;i++)
	{
	  scanf("%d",&buf[i]);
	}
 //����������Ԫ��
     for(b=0;b<n;b++)
      {
       for( j=0;j<n-1-b;j++)
	     {
	       if(buf[j]>buf[j+1])
	         temp=buf[j];
	         buf[j]=buf[j+1];
	         buf[j+1]=temp;
	     }
       }//ð��ѭ�����壬ÿ��ѭ�������������ŵ�����λ�ã�
     for(c=0;c<n;c++)
       { printf("%d ",buf[c]);}//ÿ��ѭ����ɺ󶼻���Ԫ�غ����һ���ո�
     printf("\n");//������У�
}
 return 0;
 }
