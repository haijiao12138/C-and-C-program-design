#include <iostream>
#include<stdio.h>
#include <string.h>
#include<algorithm>
using namespace std;
struct program{
	int startTime;//���ӿ�ʼʱ�� 
	int endTime;//���ӽ���ʱ�� 
	bool operator < (const program &A) const {//����С�ںţ��������� 
		return endTime<A.endTime; 
	} 
}buf[100];
int main(int argc, char** argv) {
	int n;
	while(scanf("%d",&n)!=EOF){
		if(n==0) break;
		
		for(int i=0;i<n;i++){
			scanf("%d %d",&buf[i].startTime,&buf[i].endTime);
		}
		
		sort(buf,buf+n);//���Ž���ʱ����������
		
		int currentTime=0,ans=0;
		for(int i=0;i<n;i++){
			if(currentTime<=buf[i].startTime){
				currentTime=buf[i].endTime;
				ans++;
				
			}
		}
		 
		 printf("%d",ans);
		
	}
	return 0;
}
