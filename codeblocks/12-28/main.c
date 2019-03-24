#include <stdio.h>

void Print_Factorial ( const int N );

int main()
{
    int N;

    scanf("%d", &N);
    Print_Factorial(N);
    return 0;
}
void Print_Factorial(const int N)
{
	int sum = 1;
	int i;
	if (N<0)
		printf("Invalid input");
	else if (N == 0)
		printf("1");
	else if(N>=0&&N<=12)   //程序计算阶乘正常计算到12！，一个坑
	{
		for (i = 1;i <= N;i ++ )
			{
			    sum = sum*i;
			}
			printf("%ld", sum);
	}
	else if(N>=13&&N<=1000)
    {
        int Num[3001]={0};//先设置一个足够大的数组，里面全部设置为0
        int j,k,n;
        k=1;//位数
        n=0;//进位
        Num[0]=1;//将结果先初始化为1；
        int temp;//设置暂存器，暂时存放乘法的结果
        for(i=2;i<=N;i++)//数组从2开始进行阶乘运算
        {
            for(j=0;j<k;j++)
            {

                temp=Num[j]*i+n;////相应阶乘中的一项与当前所得临时结果的某位相乘（加上进位）
                Num[j]=temp%10; //更新临时结果的位上信息
                n=temp/10;//看是否有进位

            }
            while(n!=10)
            {//如果有进位
                Num[k]=n%10;//新加一位，添加信息。位数增1
                k++;
                n=n/10;//看还能不能进位
            }
        }
        for(i=k-1;i>=0;i--)
        {
            printf("%d",Num[i]);//显示结果
        }
        printf("\n");
    }

}










