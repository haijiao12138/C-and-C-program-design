#include <iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h> 
using namespace std;
//构建结构体
struct Student{
	char no[100];
	char name[100];
	int age;
		char sex[5];
	bool  operator < (const Student &  A) const{//重载小于运算符，使其按小于排序
		return strcmp(no,A.no)<0; 
		
	}
}buf[1000];

int main(int argc, char** argv) {
	int n;
	while(scanf("%d",&n)!=EOF){
		for(int i=0;i<n;i++){
			scanf("%s %s %s %d",&buf[i].no,&buf[i].name,&buf[i].sex,&buf[i].age);//输入具体信息 
		}
		 sort(buf,buf+n);
		 
		 int t;
		 scanf("%d",&t);//一共有t组询问，
		  
		  while(t--!=0){
		  	int ans=-1;
		  	char x[30];
		  	scanf("%s",&x);//输入查找的学号
			int top=n-1,base=0;//下标初始位置，从0到n-1
			while(top>=base){
				int mid=(top+base)/2;
				int tmp=strcmp(buf[mid].no,x);
				
				if(tmp==0){//若相等，则找到所求下标，查找完跳出二分查找 
					ans=mid;
					break;
				}
				else if(tmp>0){//中间的数比要查找的数据大 
					top=mid-1;
				} 
				else 
				  base=mid+1;//中间的数比要查找的数据小， 
			} 
			if(ans==-1){
				printf("查找失败！");
			} 
			else {
			printf("%s %s %s %d\n",buf[ans].no,buf[ans].name,buf[ans].sex,buf[ans].age);
				}
			printf("\n");
		  } 
		  
	}
	return 0;
	
}










