#include <iostream>
#include<stdio.h>
#include <string.h>
#include<algorithm>
using namespace std;
struct program{
	int startTime;//电视开始时间 
	int endTime;//电视结束时间 
	bool operator < (const program &A) const {//重载小于号，升序排列 
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
		
		sort(buf,buf+n);//按着结束时间升序排列
		
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
