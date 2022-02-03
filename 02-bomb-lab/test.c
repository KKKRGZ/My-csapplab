#include<stdio.h>
int func4(int a,int b,int c)
{
  int t; // ecx
  int end; // eax
  t = (c - b) / 2 + b;
  if ( t > a )
    return 2 * func4(a, b, t - 1);
  end = 0;
  if ( t < a )
    return 2 * func4(a, t + 1, c) + 1;
  return end;
}
int main()
{
    for(int i=0;i<=14;i++)
    {   
        if(!func4(i,0,14))
            printf("%d\n",i);
    }
}