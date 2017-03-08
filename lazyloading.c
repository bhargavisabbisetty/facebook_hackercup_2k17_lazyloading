#include<stdio.h>
int main()
{
int i,j,N,W[100],t,no=1,c=0,T,r[510],res=0;
FILE *f1,*f2;
f1=fopen("lazy_loading.txt","r");
f2=fopen("lazy_loading_example_output.out","w");
fscanf(f1,"%d",&T);
while(T>0)
{
no=1;c=0;
fscanf(f1,"%d",&N);
for(i=0;i<N;i++)
{
fscanf(f1,"%d",&W[i]);
}
for(i=0;i<N;i++)
{
for(j=0;j<N;j++)
{
if(W[i]>W[j])
{
t=W[i];
W[i]=W[j];
W[j]=t;
}
}
}
for(i=0;i<=N;)
{
if(W[i]*no>50)
{
c++;
if(no==1)
{
i++;
}
else
{
N=N-no;
i++;
}
}
else
{
no++;
}
}
res++;
r[res]=c;
T--;
}
for(j=1;j<=res;j++)
{
printf("Case #%d: %d\n",j,r[j]);
fprintf(f2,"Case #%d: %d\n",j,r[j]);
}
fclose(f1);
fclose(f2);
return 0;
}
