#include<stdio.h>
int main()
{
    float open,high,low,close;
    scanf("%f %f %f %f",&open,&high,&low,&close);
    if(close<open)
    {
        printf("BW-Solid");
        if(low<open&&low<close&&high>open&&high>close)
        printf(" with Lower Shadow and Upper Shwdow");
        else if(low<open&&low<close)
             printf(" with Lower Shadow");
        else if(high>open&&high>close)
             printf(" with Upper Shwdow");
    }

    else if(close>open)
    {
       printf("R-Hollow");
       if(low<open&&low<close&&high>open&&high>close)
         printf(" with Lower Shadow and Upper Shwdow");
      else if(low<open&&low<close)
             printf(" with Lower Shadow");
        else if(high>open&&high>close)
             printf(" with Upper Shwdow");
    }

    else if(open==close)
    {
        printf("R-Cross");
        if(low<open&&low<close&&high>open&&high>close)
         printf(" with Lower Shadow and Upper Shwdow");
      else if(low<open&&low<close)
             printf(" with Lower Shadow");
        else if(high>open&&high>close)
             printf(" with Upper Shwdow");
    }

    else if(low<open&&low<close)
    {
        printf("Lower Shadow");//下影线
        if(high>open&&high>close)
             printf(" with Upper Shwdow");

    }

    else if(high>open&&high>close)
    {
        printf("Upper Shwdow");//上影线
        if(low<open&&low<close)
             printf(" with Lower Shadow");

    }

    return 0;

}
