#include<stdio.h>
#include<iostream> 
#include<algorithm>
#include<string.h>
using namespace std;
//��ʾ������Ʒ�Ľṹ��
struct goods{
	double j;//����Ʒ����
	double f;//����Ʒ�ܼ�ֵ
	double s;//����Ʒ�Լ۱�
	bool operator < (const goods &A) const {
	return s>A.s;//�����Լ۱ȱȽϸߵ�ֵ 
	} 
	
}buf[1000];
int main(){
	double m;//%lf
	int n;//%d
	while(scanf("lf %d",&m,&n)!=EOF){
		if(m==-1&&n==-1)  { break;}//��m��nΪ-1ʱ����������˳�ȥ��
		
		for(int i=0;i<n;i++){
			scanf("%lf%lf",&buf[i].j,&buf[i].f);//������Ʒ���غͼ�ֵ 
			buf[i].s=buf[i].j/buf[i].f;//�����Լ۱� 
		} 
		
		sort(buf,buf+n);//��Ʒ�����Լ۱Ƚ������� 
		int idx=0;//��ǰ���������±� 
		double ans=0; //�������������
		
		while(m>0 && idx<n){//ѭ��������������Ʒʣ��idx<n,����Ǯʣ���ʱ��m>0; 
			if(m>buf[idx].f){
				ans+=buf[idx].j;//�������
				m-=buf[idx].f;//Ǯ����� 
			}
			else{
				ans+=buf[idx].j*m/buf[idx].f;//ֻ�����²��ֲ�Ʒ
				m=0;//ûǮʣ���� 
			}
			idx++; 
		} 
		printf("%.3lf\n",ans);		 
	}
	
	return 0;
	
}/*
#include <iostream>
#include<iomanip>
#include<algorithm>
using namespace std;
typedef struct thing{
	int value;
	int weight;
	double vw;
};

bool cmp(thing a,thing b){
	return a.vw>b.vw;
}

int main() {
	int m,n,i;
	double sum;
	while(cin>>m>>n&&m!=-1&&n!=-1) {
		thing *p=new thing[n];
		for(i=0;i<n;i++){
			cin>>p[i].value>>p[i].weight;
			p[i].vw=p[i].value*1.0/p[i].weight;
		}
		
		sort(p,p+n,cmp);
		for(sum=0,i=0;i<n;i++){
			if(m>p[i].weight){
				sum+=p[i].value;
				m-=p[i].weight; 
			} 
			else{
				sum+=p[i].vw*m;
				break;
			}
		}
		cout.setf(ios::fixed);
		cout<<setprecision(3)<<sum<<endl;
	}
	return 0;
}
*/
