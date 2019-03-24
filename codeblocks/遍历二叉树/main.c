#include <stdio.h>
#include"malloc.h"
#define M 100
#include <stdlib.h>
typedef struct node//定义节信息 ，一个节点包括节点数据，左孩子和右孩子
{
    char data;//字符串型的节点数据
    struct node *lchild,*rchild;
}BTnode;
BTnode *creat()//建立二叉树
{
    BTnode *t;

    char ch;
    scanf("%c",&ch);
    if(ch=='#')
        t=NULL;
    else
    {
        t=(BTnode *)malloc(sizeof(BTnode));
        t->data=ch;
        t->lchild=creat();
        t->rchild=creat();
    }

    return t;

}
void preorder(BTnode *t)//先序遍历二叉树
{
    if(t!=NULL)
        printf("%c ",t->data);//输出节点信息
    if(t->lchild!=NULL)
        preorder(t->lchild);//输出左孩子节点信息
    if(t->rchild!=NULL)
        preorder(t->rchild);//输出右孩子节点信息
}
void inorder(BTnode *t)//中序遍历二叉树
{
    if(t!=NULL)
    {
        if(t->lchild!=NULL)
            inorder(t->lchild);//先遍历左子树
        printf("%c ",t->data);//遍历节点
        if(t->rchild!=NULL)
            inorder(t->rchild);
    }

}
void postorder(BTnode *t)
{
    if(t!=NULL)
    {
    if(t->lchild!=NULL)//遍历左子树
        postorder(t->lchild);
     if(t->rchild!=NULL)//遍历右子树
         postorder(t->rchild);
    printf("%c ",t->data);//遍历中间节点

    }
}
int main()
{
    //printf("Hello world!\n");
    BTnode  *t;
    printf("Input data :");
    t=creat();//建立二叉树函数
    printf("=====================the result============\n");
    printf("the preorder is:\n");
    preorder(t);
    printf("\n");

    printf("the inorder is:\n");
    inorder(t);
    printf("\n");

    printf("the postorder is:\n");
    postorder(t);
    printf("\n");

    getch();


    return 0;
}
ABD###CE##F##











