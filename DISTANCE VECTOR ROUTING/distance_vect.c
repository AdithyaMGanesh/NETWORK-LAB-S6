#include<stdio.h>
 
void main()
{
 int n,i,j,k;
 printf("ENTER NUM OF NODES : ");
 scanf("%d",&n);
 int cost[n][n];
 for(i=0;i<n;i++)
{
 for(j=0;j<n;j++)
 {
   scanf("%d",&cost[i][j]);
 }
}
 int nexthp[n][n];
 for(i=0;i<n;i++)
{
 for(j=0;j<n;j++)
 {
   nexthp[i][j]=-1;
 }
}
 for(i=0;i<n;i++)
{
 for(j=0;j<n;j++)
 {
  for(k=0;k<n;k++)
 { if(cost[i][j]+cost[j][k]<cost[i][k])
   {
   cost[i][k]=cost[i][j]+cost[j][k];
   nexthp[i][k]=j+65;
   }
 }
}
}
for(i=0;i<n;i++)
{ 
 printf("Routing table for %c :\n",i+65);
 printf("Dest\tNext hop\tDistance\n");
 for(j=0;j<n;j++)
 {
   if(nexthp[i][j]==-1)
      printf("%c\t-\t\t%d\n",j+65,cost[i][j]);
   else
       printf("%c\t%c\t\t%d\n",j+65,nexthp[i][j],cost[i][j]);
  printf("\n");
 }
}
}