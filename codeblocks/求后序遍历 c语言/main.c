
#include<stdio.h>
#include<stdlib.h>

#include<stdbool.h>

#include<time.h>

typedef int Ele;
typedef struct N{
	Ele *pre;
	Ele *in;

	Ele *post;
	int length;

}Node;



Node createNode(int n){

Node node;

node.length=n;

node.pre=(Ele*)malloc(sizeof(Ele)*n);

node.in=(Ele*)malloc(sizeof(Ele)*n);

node.post=(Ele*)malloc(sizeof(Ele)*n);

return node;

};



void solve(int prel,int inl,int postl,int n,Node *node){

if(n==0)return;

if(n==1){node->post[postl]=node->pre[prel];return;}

int L,R;

node->post[postl+n-1]=node->pre[prel];

int i=0;

for(;node->in[inl+i]!=node->pre[prel];i++)

;

L=i;R=n-L-1;

//printf("%d\n", L);

solve(prel+1,inl,postl,L,node);

solve(prel+L+1,inl+L+1,postl+L,R,node);

}

int main(){

	int n=0;

	scanf("%d",&n);

Node node=createNode(n);
int i;
for( i=0;i<n;i++)

	scanf("%d",&node.pre[i]);

for( i=0;i<n;i++)

	scanf("%d",&node.in[i]);

solve(0,0,0,n,&node);

for( i=0;i<n;i++)

	printf("%d ",node.post[i]);

	return 0;

}


