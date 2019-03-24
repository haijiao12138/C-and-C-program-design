#include <iostream>
#include<stdio.h>
int gcd(int a,int b){
	if(b==0){
		return a;
	} 
	else{//b!=0
		return gcd(b,a%b);
	}
}
int main(int argc, char** argv) {
	int a,b;
	while(scanf("%d %d",&a,&b)!=EOF){
		printf("%d\n",gcd(a,b));
	}
}
