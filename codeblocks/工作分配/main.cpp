#include<iostream>
using namespace std;
#define N 21
int cost[N][N];
int a[N];
int n,cv;
int bestv=1000;

void backtrack(int t)
{
        if(t>n)
        {
                if(cv<bestv)
                        bestv=cv;
               // return;
        }
        else
        {
                for(int i=t;i<=n;i++)
                {
                        cv+=cost[t][a[i]];
                        swap(a[t],a[i]);
                        if(cv < bestv)
                                backtrack(t+1);
                        swap(a[t],a[i]);
                        cv-= cost[t][a[i]];
                }
        }
}

int main()
{
        int i,j;
        while(cin>>n)
        {
                for(i=1;i<=n;i++)
                        for(j=1;j<=n;j++)
                                cin>>cost[i][j];
                for(i=1;i<=n;i++)
                        a[i]=i;
                backtrack(1);
                cout<<bestv<<endl;
        }
        return 0;
}
