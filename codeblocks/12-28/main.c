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
	else if(N>=0&&N<=12)   //�������׳��������㵽12����һ����
	{
		for (i = 1;i <= N;i ++ )
			{
			    sum = sum*i;
			}
			printf("%ld", sum);
	}
	else if(N>=13&&N<=1000)
    {
        int Num[3001]={0};//������һ���㹻������飬����ȫ������Ϊ0
        int j,k,n;
        k=1;//λ��
        n=0;//��λ
        Num[0]=1;//������ȳ�ʼ��Ϊ1��
        int temp;//�����ݴ�������ʱ��ų˷��Ľ��
        for(i=2;i<=N;i++)//�����2��ʼ���н׳�����
        {
            for(j=0;j<k;j++)
            {

                temp=Num[j]*i+n;////��Ӧ�׳��е�һ���뵱ǰ������ʱ�����ĳλ��ˣ����Ͻ�λ��
                Num[j]=temp%10; //������ʱ�����λ����Ϣ
                n=temp/10;//���Ƿ��н�λ

            }
            while(n!=10)
            {//����н�λ
                Num[k]=n%10;//�¼�һλ�������Ϣ��λ����1
                k++;
                n=n/10;//�����ܲ��ܽ�λ
            }
        }
        for(i=k-1;i>=0;i--)
        {
            printf("%d",Num[i]);//��ʾ���
        }
        printf("\n");
    }

}










