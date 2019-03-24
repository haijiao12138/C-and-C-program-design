#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void main(){
char id[6]={'\0'};
int i;
char arr[10]={'0','1','2','3','4','5','6','7','8','9'};//пртк╡йф╠
srand((unsigned)time(NULL));
int a;
for (i=0;i<5;i++)
{
a=rand()%10;
id[i] =arr[a] ;
}
printf("中奖的号码为：%s\n",id);
return 0;
}
