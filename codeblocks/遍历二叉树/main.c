#include <stdio.h>
#include"malloc.h"
#define M 100
#include <stdlib.h>
typedef struct node//�������Ϣ ��һ���ڵ�����ڵ����ݣ����Ӻ��Һ���
{
    char data;//�ַ����͵Ľڵ�����
    struct node *lchild,*rchild;
}BTnode;
BTnode *creat()//����������
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
void preorder(BTnode *t)//�������������
{
    if(t!=NULL)
        printf("%c ",t->data);//����ڵ���Ϣ
    if(t->lchild!=NULL)
        preorder(t->lchild);//������ӽڵ���Ϣ
    if(t->rchild!=NULL)
        preorder(t->rchild);//����Һ��ӽڵ���Ϣ
}
void inorder(BTnode *t)//�������������
{
    if(t!=NULL)
    {
        if(t->lchild!=NULL)
            inorder(t->lchild);//�ȱ���������
        printf("%c ",t->data);//�����ڵ�
        if(t->rchild!=NULL)
            inorder(t->rchild);
    }

}
void postorder(BTnode *t)
{
    if(t!=NULL)
    {
    if(t->lchild!=NULL)//����������
        postorder(t->lchild);
     if(t->rchild!=NULL)//����������
         postorder(t->rchild);
    printf("%c ",t->data);//�����м�ڵ�

    }
}
int main()
{
    //printf("Hello world!\n");
    BTnode  *t;
    printf("Input data :");
    t=creat();//��������������
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











