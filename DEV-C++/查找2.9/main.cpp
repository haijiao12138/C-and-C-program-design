#include <iostream>
#include<stdio.h>
//找x; 
int main(int argc, char** argv) {
	int buf[200];
	int n;
	while(scanf("%d",&n)!=EOF){
		for(int i=0;i<n;i++){
			scanf("%d",&buf[i]);
		}
		
		int x,ans=-1;//查找x的坐标，初始答案为-1，找不到时返回初始值-1
		
		scanf("%d",&x);
		for(int i=0;i<n;i++){
			if(x==buf[i]){
				ans=i;
				break;//查找成功时，强制退出 
			}			
		}
		printf("%d",ans); 
		
	}
	return 0;
}
