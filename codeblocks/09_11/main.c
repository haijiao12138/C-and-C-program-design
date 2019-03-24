
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void main(){
char id[6]={'\0'};
int i;
char arr[36]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};//³µÅÆºÅ
srand((unsigned)time(NULL));
int a;
for (i=0;i<5;i++)
{
a=rand()%36;
id[i] =arr[a] ;
}
printf("车牌号码为：%s\n",id);
return 0;
}
