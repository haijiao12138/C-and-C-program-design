#include <stdio.h>
#include <stdlib.h>
#include<string.h>
 typedef struct Node
{
  struct Node *lchild;//左孩子
struct Node *rchild;//右孩子
    char  c;//节点数据信息
}Tree[50];
int loc;//静态数组中已经分配的节点个数
Node *creat()//申请一个节点空间，返回指向其的指针
{
    Tree[loc].lchild=Tree[loc].rchild=NULL;
    return  &Tree[loc++];
}
char str1[30],str2[30];
void postorder(Node *T)//后序遍历
{
    if(T->lchild!=NULL)//遍历左子树
    {
        postorder(T->lchild);
    }
    if(T->rchild!=NULL)//遍历右子树
    {
        postorder(T->rchild);
    }
    printf("%c",T->c);
}
Node *build(int s1,int e1,int s2,int e2)//前序遍历从str1[s1]到str[e1],中序遍历从str1[s2]到str[e2],
{
    Node  *ret=creat();//为该树根节点申请空间
    ret->c=str1[s1];//该节点字符为前序遍历的第一个字符
    int  rootIdx;
    for(int i=s2;i<e2;i++)
    {
        if(str2[i]==str1[s1])
        {
            rootIdx==i;
            break;
        }
    }
    if(rootIdx!=s2)
    {
        ret->lchild=build(s1+1,s1+(rootIdx-s2),s2,rootIdx-1);
    }
    if(rootIdx!=e2)
    {

        ret->rchild=build(s1+(rootIdx-s2)+1,e1,rootIdx+1,e2);
    }
    return ret;
}

int main()
{
    while(scanf("%s",str1)!=EOF)
    {
        scanf("%s",str2);
        loc=0;
        int L1=strlen(str1);
        int L2=strlen(str2);
        Node *T=build(0,L1-1,0,L2-1);
        postOrder(T);
        printf("\n");
    }
    //printf("Hello world!\n");
    return 0;
}
