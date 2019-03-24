
#include <iostream>
using namespace std;
#define MAXSIZE 50;
typedef int keyType;//自定义数据类型

typedef struct
{
    keyType key;
}ElemType;

typedef struct
{
    ElemType *R;
    int length;
}SSTable;

void Create(SSTable &T)
{
    int i;
 T.R=new ElemType[MAXSIZE+1];
    cin>>T.length;
    for(i=1;i<=T.length;i++)
    {
        cin>>T.R[i].key;
    }
}
int Search_bin(SSTable T,keyType k);
int main()
{
    SSTable T;
    KeyType k;
    Create(T);
    cin>>k;
    int pos=Search_bin(T,k);
    if(pos==0)
       cout<<"NOT FOUND"<<endl;
    else
       cout<<pos<<endl;
    return 0;
}
int Search_bin(SSTable T,keyType k)
{
    int j;
    for(j=1;j<=T.length;)
      {
          if(k==T.R[i].key)
             return j;
           else
             j++;
      }

}
