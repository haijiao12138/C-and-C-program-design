#include <iostream>
#include<stdio.h>
//��x; 
int main(int argc, char** argv) {
	int buf[200];
	int n;
	while(scanf("%d",&n)!=EOF){
		for(int i=0;i<n;i++){
			scanf("%d",&buf[i]);
		}
		
		int x,ans=-1;//����x�����꣬��ʼ��Ϊ-1���Ҳ���ʱ���س�ʼֵ-1
		
		scanf("%d",&x);
		for(int i=0;i<n;i++){
			if(x==buf[i]){
				ans=i;
				break;//���ҳɹ�ʱ��ǿ���˳� 
			}			
		}
		printf("%d",ans); 
		
	}
	return 0;
}
