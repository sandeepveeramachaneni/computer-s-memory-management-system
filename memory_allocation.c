#include<stdio.h>
#include<process.h>
#include <stdlib.h>
void main()
{
void memory_allocation(int a[20],int p[20],int count){
int i,j,n,m,fragments,average_fragments=0;
printf("Enter no of Blocks.\n");
scanf("%d",&n);
for(i=0;i<n;i++)
{
                        printf("Enter the %dst Block size:",i);
                        scanf("%d",&a[i]);
}
printf("Enter no of Process.\n");
scanf("%d",&m);
for(i=0;i<m;i++)
{
                        printf("Enter the size of %dst Process:",i);
                        scanf("%d",&p[i]);
}
            for(i=0;i<n;i++)
{
for(j=0;j<m;j++)
                        {
                                    if(p[j]<=a[i])
                                    {
                                                printf("Allocation is in progress.....\n");
                                                sleep(5);
                                                printf("The Process %d allocated to block size %d\n",j,a[i]);
                                                fragments=a[i]-p[j];
                                                printf("Fragments are %d\n",fragments);
                                                average_fragments=average_fragments+fragments;
                                                p[j]=10000;
                                                break;
                                    }
                        }
}
for(j=0;j<m;j++)
{
if(p[j]!=10000)
                        {
printf("The Process %d is not allocated to any Block,Due to insufficient resources.",j);
                        }
}
printf("The average number of Fragments left are %d\n",average_fragments);


count++;
main();
}
void memory_deallocation(int a[20],int p[20]){

    printf("The data is deallocated\n");



    main();
}


int num,count=0;
int a[20]={0};
int p[20]={0};



printf("1. Memory Allocation \n");
printf("2. Memory Deallocation \n");
printf("Enter the process that you want to do :");
scanf("%d",&num);

switch(num){
case 1:
    memory_allocation(a,p,count);
    count++;
    break;
case 2:
    if(count>0){
    printf("already free");
    count--;
    }
    else{
    memory_deallocation(a,p);
    }
    break;
default:
    printf("Incorrect Input");
    break;

}

}



