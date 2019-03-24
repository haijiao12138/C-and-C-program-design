#include<iostream>
#include<stdio.h>
using namespace std;
int ab,c,n,ji[200],h[200];
struct bag
{
    int w;
    int h;
} b[200];
void digui(int d,int s,int sc)      //d为第几个物品，为当前价值，sc为当前所占质量
{
    if(sc>c)return;                 //如果当前质量大于容量返回
    if(d==n)                        //如果所有物品检验完毕
    {
        if(ab<s)                    //当前价值小于最大价值
        {
            ab=s;
            for(int i=0; i<d; i++)  //记录此时物品放置信息
                h[i]=ji[i];
        }
    }
    else for(int i=0; i<2; i++)
        {
            if(i==0)ji[d]=0,digui(d+1,s,sc);    //不放入当前物品
            else ji[d]=1,digui(d+1,s+b[d].w,sc+b[d].h); //放入当前物品
        }
}
int main()
{
    cin>>n>>c;
    for(int i=0; i<n; i++)
        cin>>b[i].w;            //输入价值
    for(int i=0; i<n; i++)
        cin>>b[i].h;            //输入重量
    digui(0,0,0);               //递归函数
    printf("Optimal value is\n%d\n",ab);
    for(int i=0; i<n; i++)
        printf(i!=n-1?"%d ":"%d\n",h[i]);
    return 0;
}
