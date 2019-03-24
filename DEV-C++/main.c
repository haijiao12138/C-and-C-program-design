#include<stdio.h>
//#define _CRT_SECURE_NO_WARNINGS
int main()
{
	int n;
	int buf[100];
	int i, j, temp;
	while (scanf_s("%d", &n) != EOF) {//当输入的数据有效时，
		for (i = 0;i<n;i++) {
			scanf_s("%d", &buf[i]);//输入将要排序的数字
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
		}//冒泡循环主体

		for (i = 0;i<n;i++) {
			printf("%d ", buf[i]);
		}
	

	}//while
	return 0;
}
