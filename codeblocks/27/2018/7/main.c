#include <stdio.h>

int Factorial( const int N );

int main()
{
    int N, NF;

    scanf("%d", &N);
    NF = Factorial(N);
    if (NF)  printf("%d! = %d\n", N, NF);
    else printf("Invalid input\n");

    return 0;
}
int Factorial(const int N)
{
  int i;
  int sum;
  if(N>=0&&N<12)
  {
    sum=1;
    for(i=1;i<=N;i++)
    {
    sum=sum*i;
    }
  }
  else
    sum=0;

  return sum;
}
