//sort��������
#include<stdio.h>
#include<algorithm>
using namespace std;
bool cmp(int x,int y){
	//�Զ�������
	return x>y; 
} 
int main(){
	int n;
	int buf[100];
	while(scanf("%d",&n)!=EOF){
		for(int i=0;i<n;i++)
		{
			scanf("%d",&buf[i]);
		}
		sort(buf,buf+n,cmp);//ʹ���Զ������� 
		for(int i=0;i<n;i++)
		{
			printf("%d ",buf[i]);
		}
	} 
	return 0; 
} 
