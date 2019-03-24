#include<stdio.h>
int main()
{
    int j,k,n,count;
    int index=0,sum=0;
    int i=2;
    int a[100]={0};
    a[2]=2;
    scanf("%d",&n);
    if(n==1)
        printf("1");
else
  {

    while(n-sum>=i) { //从2开始，对n进行分解
        sum+=i;
        a[i]=i;
        i++;
        index++;
    }
    int p=(n-sum)/index; //整体全部累加
    int q=(n-sum)%index; //只从后往前，加最后剩余的
    for(j=i-1;j>=2;j--) {
        a[j]+=p;
    }
    for(k=i-1;k>i-1-q;k--) {
        a[k]++;
    }
    int summ=1;
    for(j=2;j<index+2;j++)
     summ=summ*a[j];
        printf("%d\n",summ);
  }

}

/*#include<stdio.h>
int main()
{
    int j,k,n,count;
    int index=0,sum=0;
    int i=2;
    int a[100]={0};
    a[2]=2;
    scanf("%d",&n);
    while(n-sum>=i) { //从2开始，对n进行分解
        sum+=i;
        a[i]=i;
        i++;
        index++;
    }
    int p=(n-sum)/index; //整体全部累加
    int q=(n-sum)%index; //只从后往前，加最后剩余的
    for(j=i-1;j>=2;j--) {
        a[j]+=p;
    }
    for(k=i-1;k>i-1-q;k--) {
        a[k]++;
    }
 for(j=2;j<index+2;j++) {
        printf("%d  ",a[j]);
 }
    int summ=1;
    for(j=2;j<index+2;j++)
     summ=summ*a[j];
        printf("%d\n",summ);
}
*/

