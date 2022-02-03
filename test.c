#include<stdio.h>
#include<stdlib.h>
int main()
{
    int l,r,mid,n,x,pos=0,num=0,flag=0;
    int a[20];
    printf("number:\n");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    printf("need selecrt:\n");
    scanf("%d",&x);
    l=0,r=n-1;
    mid=(l+r)/2;
    while(l!=r)
    {
        if(a[mid]>x)
        {
            r=mid;
            mid=(r+l)/2;
            num++;
        }
        else if(a[mid]<x)
        {
            l=mid+1;
            mid=(r+l)/2;
            num++;
        }
    }
    if(a[l]==x)
    {
        num++;
        flag=1;
        pos = l;
    }
    if(flag==1)
    {
        printf("position %d num %d",pos,num);
    }
    else
    {
        printf("no found");
    }

}
