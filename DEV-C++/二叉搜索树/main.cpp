#include <iostream>
#include<stdio.h>
#include<string.h>
struct Node{
	Node *lchild;
	Node *rchild;
	int c;
}Tree[110];
int loc;//
Node *creat(){
	Tree[loc].lchild=Tree[loc].rchild=NULL;
	return &Tree[loc++];
}
char str1[25],str2[25];//保存二叉排序树遍历结果

int size1,size2;
char *str;//当前正在保存字符串 
int *size;//当前正在保存字符串中的字符个数 

 void postOrder(Node *T){//前序遍历 
 	if(T->lchild!=NULL){
 		postOrder(T->lchild);
	 }
	if(T->rchild!=NULL){
 		postOrder(T->rchild);
	 }
	 str[(*size)++]=T->c+'0';//将节点中的字符放入正在保存的字符串中 
	 
 } 
 
 void inOrder(Node *T){//中序遍历 
 	if(T->lchild!=NULL){
 		inOrder(T->lchild);
	 }
	 str[(*size)++]=T->c+'0';//将节点中的字符放入正在保存的字符串中 
	if(T->rchild!=NULL){
 		inOrder(T->rchild);
	 }
	 
 } 
 Node *Insert(Node *T,int x){
 	if(T==NULL){
 		T=creat();
 		T->c=x;
 		return T;
	 }
	 else if(x<T->c){
	 	
	    T->lchild=Insert(T->lchild,x);
	}
	else if(x>T->c){
		 T->rchild=Insert(T->rchild,x);
	}
	return T;
	
 }
 

int main() {
	int n;
	char tmp[12];
	while(scanf("%d",&n)!=EOF&&n!=0){
		loc=0;
		Node *T=NULL;
		scanf("%s",tmp);//输入字符串
		for(int i=0;tmp[i]!=0;i++){
			T=Insert(T,tmp[i]-'0');//按顺序将字符插入二叉排序树 
		} 
		size1=0;
		str=str1;
		size=&size1;
		postOrder(T);//前序遍历
		inOrder(T);//中序遍历
		str1[size1]=0;//向第一个字符串的最后一个字符添加空字符，方便使用字符串函数
	while(n--!=0){
		scanf("%s",tmp);//输入字符串
			Node *T2=NULL;
		for(int i=0;tmp[i]!=0;i++){
			T2=Insert(T2,tmp[i]-'0');//按顺序将字符插入二叉排序树 
		} 
		size2=0;
		str=str2;
		size=&size2;
		postOrder(T2);//前序遍历
		inOrder(T2);//中序遍历
		str2[size2]=0;//向第一个字符串的最后一个字符添加空字符，方便使用字符串函数
		puts(strcmp(str1,str2)==0 ? "YES" :"NO");
	} 
	}
	return 0;
}
















