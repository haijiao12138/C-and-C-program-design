 #include<stdio.h>
 int main()
 {
 int n;
 int buf[100];//定义一个足够大的数组，用来存储要 排序的数组
 int i,j;
 int a,b,c;
 int temp;
 while(scanf("%d",&n)!=EOF)
 {
    for( i=0;i<n;i++)
	{
	  scanf("%d",&buf[i]);
	}
 //输入待排序的元素
     for(b=0;b<n;b++)
      {
       for( j=0;j<n-1-b;j++)
	     {
	       if(buf[j]>buf[j+1])
	         temp=buf[j];
	         buf[j]=buf[j+1];
	         buf[j+1]=temp;
	     }
       }//冒泡循环主体，每次循环都将最大的数放到最后的位置，
     for(c=0;c<n;c++)
       { printf("%d ",buf[c]);}//每次循环完成后都会在元素后面加一个空格
     printf("\n");//输出换行，
}
 return 0;
 }
