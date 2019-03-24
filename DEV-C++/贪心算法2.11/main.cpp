#include<stdio.h>
#include<iostream> 
#include<algorithm>
#include<string.h>
using namespace std;
//表示购买物品的结构体
struct goods{
	double j;//该物品总重
	double f;//该物品总价值
	double s;//该物品性价比
	bool operator < (const goods &A) const {
	return s>A.s;//返回性价比比较高的值 
	} 
	
}buf[1000];
int main(){
	double m;//%lf
	int n;//%d
	while(scanf("lf %d",&m,&n)!=EOF){
		if(m==-1&&n==-1)  { break;}//当m和n为-1时，程序结束退出去，
		
		for(int i=0;i<n;i++){
			scanf("%lf%lf",&buf[i].j,&buf[i].f);//输入物品总重和价值 
			buf[i].s=buf[i].j/buf[i].f;//计算性价比 
		} 
		
		sort(buf,buf+n);//物品按着性价比降序排列 
		int idx=0;//当前货物索引下标 
		double ans=0; //货物相加总重量
		
		while(m>0 && idx<n){//循环条件，既有物品剩余idx<n,又有钱剩余的时候m>0; 
			if(m>buf[idx].f){
				ans+=buf[idx].j;//重量相加
				m-=buf[idx].f;//钱数相减 
			}
			else{
				ans+=buf[idx].j*m/buf[idx].f;//只能买下部分产品
				m=0;//没钱剩余了 
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
