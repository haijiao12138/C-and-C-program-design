#include <stdio.h>
#include <stdlib.h>
#include<string.h>
 typedef struct Node
{
  struct Node *lchild;//����
struct Node *rchild;//�Һ���
    char  c;//�ڵ�������Ϣ
}Tree[50];
int loc;//��̬�������Ѿ�����Ľڵ����
Node *creat()//����һ���ڵ�ռ䣬����ָ�����ָ��
{
    Tree[loc].lchild=Tree[loc].rchild=NULL;
    return  &Tree[loc++];
}
char str1[30],str2[30];
void postorder(Node *T)//�������
{
    if(T->lchild!=NULL)//����������
    {
        postorder(T->lchild);
    }
    if(T->rchild!=NULL)//����������
    {
        postorder(T->rchild);
    }
    printf("%c",T->c);
}
Node *build(int s1,int e1,int s2,int e2)//ǰ�������str1[s1]��str[e1],���������str1[s2]��str[e2],
{
    Node  *ret=creat();//Ϊ�������ڵ�����ռ�
    ret->c=str1[s1];//�ýڵ��ַ�Ϊǰ������ĵ�һ���ַ�
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
