#include<stdio.h>
#define min(x,y) (x<y)?x:y
void main()
{
 int oprate,bsize,rem=0,npack =0;
 int recv,sent,drop =0,ch,i=0;
 int input[100];
 printf("Enter bucketsize :");
 scanf("%d",&bsize);
 printf("Enter op rate :");
 scanf("%d",&oprate);
 do
{
 printf("Enter input t %d sec :",i+1);
 scanf("%d",&input[i]);
i++;
 printf("Enter 0 or 1  ");
 scanf("%d",&ch);
}while(ch);
npack = i;
printf("Time\tReceived\tSent\tDrop\tRemaining\n");
for(i=0;i<npack||rem>0;i++)
{
 recv = input[i];
 sent = min(oprate,recv+rem);
 if(recv+rem>bsize)
{
 drop = recv+rem - bsize;
 recv -= drop; 
}
else 
 drop=0;
rem = rem+recv-sent;
if(rem<0) rem =0;
printf("%2d\t%8d\t%4d\t%6d\t%9d\n",i+1,input[i],sent,drop,rem);

}
}