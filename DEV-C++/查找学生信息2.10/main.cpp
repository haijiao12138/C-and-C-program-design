#include <iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h> 
using namespace std;
//�����ṹ��
struct Student{
	char no[100];
	char name[100];
	int age;
		char sex[5];
	bool  operator < (const Student &  A) const{//����С���������ʹ�䰴С������
		return strcmp(no,A.no)<0; 
		
	}
}buf[1000];

int main(int argc, char** argv) {
	int n;
	while(scanf("%d",&n)!=EOF){
		for(int i=0;i<n;i++){
			scanf("%s %s %s %d",&buf[i].no,&buf[i].name,&buf[i].sex,&buf[i].age);//���������Ϣ 
		}
		 sort(buf,buf+n);
		 
		 int t;
		 scanf("%d",&t);//һ����t��ѯ�ʣ�
		  
		  while(t--!=0){
		  	int ans=-1;
		  	char x[30];
		  	scanf("%s",&x);//������ҵ�ѧ��
			int top=n-1,base=0;//�±��ʼλ�ã���0��n-1
			while(top>=base){
				int mid=(top+base)/2;
				int tmp=strcmp(buf[mid].no,x);
				
				if(tmp==0){//����ȣ����ҵ������±꣬�������������ֲ��� 
					ans=mid;
					break;
				}
				else if(tmp>0){//�м������Ҫ���ҵ����ݴ� 
					top=mid-1;
				} 
				else 
				  base=mid+1;//�м������Ҫ���ҵ�����С�� 
			} 
			if(ans==-1){
				printf("����ʧ�ܣ�");
			} 
			else {
			printf("%s %s %s %d\n",buf[ans].no,buf[ans].name,buf[ans].sex,buf[ans].age);
				}
			printf("\n");
		  } 
		  
	}
	return 0;
	
}










