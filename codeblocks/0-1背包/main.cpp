#include<iostream>
#include<stdio.h>
using namespace std;
int ab,c,n,ji[200],h[200];
struct bag
{
    int w;
    int h;
} b[200];
void digui(int d,int s,int sc)      //dΪ�ڼ�����Ʒ��Ϊ��ǰ��ֵ��scΪ��ǰ��ռ����
{
    if(sc>c)return;                 //�����ǰ����������������
    if(d==n)                        //���������Ʒ�������
    {
        if(ab<s)                    //��ǰ��ֵС������ֵ
        {
            ab=s;
            for(int i=0; i<d; i++)  //��¼��ʱ��Ʒ������Ϣ
                h[i]=ji[i];
        }
    }
    else for(int i=0; i<2; i++)
        {
            if(i==0)ji[d]=0,digui(d+1,s,sc);    //�����뵱ǰ��Ʒ
            else ji[d]=1,digui(d+1,s+b[d].w,sc+b[d].h); //���뵱ǰ��Ʒ
        }
}
int main()
{
    cin>>n>>c;
    for(int i=0; i<n; i++)
        cin>>b[i].w;            //�����ֵ
    for(int i=0; i<n; i++)
        cin>>b[i].h;            //��������
    digui(0,0,0);               //�ݹ麯��
    printf("Optimal value is\n%d\n",ab);
    for(int i=0; i<n; i++)
        printf(i!=n-1?"%d ":"%d\n",h[i]);
    return 0;
}
