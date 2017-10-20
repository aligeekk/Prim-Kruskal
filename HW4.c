#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#define MAX 1000
typedef struct
{
    int x, y;
    int w;
}edge;

int set[11];
int set1[11];

void sort(edge a[],int n)
{
    int x,y;
    edge temp;
    for(x=0;x<n-1;x++) {
        for(y=x+1;y<n;y++) {
            if(a[x].w>a[y].w) {
                temp=a[x];
                a[x]=a[y];
                a[y]=temp;
            }
        }
    }
}

int find3(int x)
{
    int root,node,parent;
    root=x;
    while(root!=set1[root])
        root=set1[root];
    node=x;
    while(node!=root)
    {
        parent=set1[node];
        set1[node]=root;
        node=parent;
    }
    return root;
}

void union3(int repx, int repy,int height[])
{
    if (height[repx] == height [repy])
    {
        height[repx]++;
        set1[repy] = repx;//y’s tree points to x’s tree
    }
    else if (height[repx] > height [repy])
        set1[repy]=repx;//y’s tree points to x’stree
    else
        set1[repx]=repy; //x’s tree points to y’stree
}

void Kruskal (int *A,int n)
{
    int i,j,index,ucomp,vcomp;
    int height[n];
    edge E[n*n],T[n*n];
    index=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            E[index].w = A[i*n+j];
            E[index].x=i;
            E[index].y=j;
            index++;
        }
    }
    sort(E,n*n);//first sort the edge
    
    for (i = 0;i < n;i++)//make a set
    {
        set1[i] = i;
        height[i] = 0;
    }

    index=0;
    for(i=0;i<n*n;i++)
    {
        if(E[i].w!=0)
        {
            ucomp=find3(E[i].x);
            vcomp=find3(E[i].y);
            if(vcomp!=ucomp)
            {
                T[index]=E[i];
                union3(ucomp,vcomp,height);
                index++;
                if(index==n-1)
                    break;
            }
        }
    }
    printf("======Kruskal=======minimum spanning tree:\n");
    for(i=0;i<n-1;i++)
    {
        printf("edge:%d - %d,weight:%d\n",T[i].x,T[i].y,T[i].w);
    }
}


void Prim(int *A,int n)
{
    int prev[n];
    int cost[n];
    //int set[n];
    int i,min,min1,count;
    min=MAX;
    count=0;
    for(i=0;i<n;i++)
    {
        cost[i]=MAX;
        set[i]=0;
    }
    //set 0 as root
    cost[0]=0;
    prev[0]=-1;

 while(count<n-1)
 {
        for(i=0;i<n;i++)
        {
            if(set[i]== 0 && cost[i]< min)
            {
                    min = cost[i];
                    min1 = i;
            }          
         }
        set[min1] = 1;
        //min1 as next node 
        for(i=0;i<n;i++)
        {
            if(A[min1*n+i] > 0 && cost[i]>A[min1*n+i] && set[i]==0)
            {
                    cost[i] = A[min1*n+i];
                    prev[i] = min1;
            }
        }
        min = MAX;
        count++;
 }
//print 
 printf("======Prim=======minimum spanning tree:\n");
for (i = 1; i < n; i++)
       printf("edge:%d - %d,weight: %d \n", prev[i], i, A[prev[i]*n+i]);
}



int main(int argc, char const *argv[])
{
    int i,j,n;
    int flag;
    int *A;
    srand(time(NULL));
    n = (rand()%6)+5;//rang between 5-10
    //====================
    //n = 5;
    printf("start :n vertices rang between 5 to 10,n=%d \n",n);
    A = (int *)malloc(sizeof(int)*(n * n));// matrix A
    for(i=0;i<n;i++)
        for(j=0;j<=i;j++)
        {
            if(i==j)
            {
                A[i*n+j]=0;
            }
            else
            {
                A[i*n+j]=rand()%10+1;
                A[j*n+i]=A[i*n+j];//make A[i,j] = A[j,i]
            }
        }
    printf("======matrix A:======\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",A[i*n+j]);
        }
        printf("\n");
    }
    // Prim(A,n);
    // Kruskal(A,n);
    printf("Press 1:Prim\nPress 2:Kruskal\nPress 12 run both Prim and Kruskal to check answer\n");
    while(scanf("%d",&flag))
    {
    //scanf("%d",&flag)
    if (flag==1)
    {
        Prim(A,n);
        break;
    }
    else if(flag==2)
    {
        Kruskal(A,n);
        break;
    }
    else if(flag==12)
    {
        Prim(A,n);
        Kruskal(A,n);
        break;
    }
    else
        printf("error! please input 1 or 2 or 12\n");
    }
}




