#include<stdio.h>
//#define _CRT_SECURE_NO_WARNINGS
int main()
{
	int n;
	int buf[100];
	int i, j, temp;
	while (scanf_s("%d", &n) != EOF) {//�������������Чʱ��
		for (i = 0;i<n;i++) {
			scanf_s("%d", &buf[i]);//���뽫Ҫ���������
		}

		for (i= 0;i<n;i++) {
			for (j = 0;j<n - i - 1;j++)
			{
				if (buf[j]>buf[j + 1]) {
					temp = buf[j];
					buf[j] = buf[j + 1];
					buf[j + 1] = temp;

				}
			}
		}//ð��ѭ������

		for (i = 0;i<n;i++) {
			printf("%d ", buf[i]);
		}
	

	}//while
	return 0;
}
