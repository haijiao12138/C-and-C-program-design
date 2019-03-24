/*****
Language:C++
*****/
#include <iostream>
using namespace std;

#include<string.h>
#include<algorithm>

struct Node
{
    char number[7];
    char name[9];
    int score;
};
bool Cmp1(Node a,Node b)
{
    return strcmp(a.number ,b.number)<0;//i字符串1大于2，返回值为正数
    //true，a<b
    //false ,a>b;
}

bool Cmp2(Node a,Node b)
{
    if(strcmp(a.name,b.name)!=0)
    {
        return strcmp(a.name,b.name)<0;//true,a<b;
    }
     return strcmp(a.number,b.number)>0;//reue,a>b;
}

bool Cmp3(Node a,Node b)
{
    if(a.score!=b.score)
    {
        return a.score<b.score;
    }
    return strcmp(a.number,b.number)<0;//a<b,true
}
Node node[100000];
int main()
{
    int n,c,i;
    int count=1;
    while(cin>>n>>c)
    {
        if(n==0)
        {
            return 0;
        }
        else
        {
            for(i=0;i<n;i++)
            {
                cin>>node[i].number>>node[i].name>>node[i].score;

            }
            switch(c)
            {
            case 1:
                {
                    sort(node,node+n,Cmp1);
                    break;
                }
            case 2:
                {
                    sort(node,node+n,Cmp2);
                    break;
                }
            case 3:
                {
                    sort(node,node+n,Cmp3);
                    break;
                }
            }
            cout<<" Case "<<count++<<" : "<<endl;
            for(i=0;i<n;i++)
            {
                cout<<node[i].number<<" "<<node[i].name<<" "<<node[i].score<<endl;
            }
        }
    }
    return 0;

}







