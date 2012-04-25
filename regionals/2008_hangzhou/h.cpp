#include <iostream>
#include <cstdio>
using namespace std;

int n1, n2, m;
int dfa1[2000][26], dfa2[2000][26];
bool d1[2000], d2[2000], g[2000][2000], g1[2000][2000], g2[2000][2000], can1[2000], can2[2000];
struct Node{int i; int j;}queue[4000000];
int front, rear;
bool visited[2000], q[2000], f, r;

void bfs(bool flag[], bool graph[2000][2000], int n, int from)
{
    q[0]=from;
    f=0;
    r=1;
    while(f!=r)
    {
        int now=q[front];
        for(int i=0; i<n; ++i)
            if(graph[i][now]&&!visited[i])
            {
                visited[i]=true;
                flag[i]=true;
                q[r++]=i;
            }
        ++f;
    }
}

void init()
{
    for(int i=0; i<n1; ++i) for(int j=0; j<n1; ++j) g1[i][j]=false;
    for(int i=0; i<n2; ++i) for(int j=0; j<n2; ++j) g2[i][j]=false;
    for(int i=0; i<n1; ++i)
        for(int j=0; j<m; ++j)
            g1[i][dfa1[i][j]]=true;
    for(int i=0; i<n2; ++i)
        for(int j=0; j<m; ++j)
            g2[i][dfa2[i][j]]=true;
    for(int i=0; i<n1; ++i) {can1[i]=visited[i]=false;}
    for(int i=0; i<n1; ++i) if(d1[i]) bfs(can1, g1, n1, i);
    for(int i=0; i<n2; ++i) {can2[i]=visited[i]=false;}
    for(int i=0; i<n2; ++i) if(d2[i]) bfs(can2, g2, n2, i);
}

void calculate()
{
    init();
    if(d1[0]!=d2[0])
    {
        printf("No\n");
        return;
    }
    for(int i=0; i<n1; ++i) for(int j=0; j<n2; ++j) g[i][j]=false;
    g[0][0]=true;
    front=0;
    rear=1;
    queue[0].i=queue[0].j=0;
    while(front!=rear)
    {
        int i=queue[front].i, j=queue[front].j;
        for(int k=0; k<m; ++k)
            if(dfa1[i][k]==-1&&dfa2[j][k]==-1)
            {
            }
            else if(dfa1[i][k]==-1&&dfa2[j][k]!=-1)
            {
                if(can2[dfa2[j][k]]){printf("No\n"); return;}
            }
            else if(dfa1[i][k]!=-1&&dfa2[j][k]==-1)
            {
                if(can1[dfa1[i][k]]){printf("No\n"); return;}
            }
            else if(dfa1[i][k]!=-1&&dfa2[j][k]!=-1&&!g[dfa1[i][k]][dfa2[j][k]])
            {
                g[dfa1[i][k]][dfa2[j][k]]=true;
                if(d1[dfa1[i][k]]!=d2[dfa2[j][k]])
                {
                    printf("No\n");
                    return;
                }
                queue[rear].i=dfa1[i][k];
                queue[rear++].j=dfa2[j][k];
            }
        ++front;
    }
    printf("Yes\n");
}

int main()
{
    int t1=1, t2;
    while(scanf("%d", &m), m)
    {
        scanf("%d", &n1);
        for(int i=0; i<n1; ++i)
        {
            scanf("%d", &t2);
            if(t2==1) d1[i]=true;
            else d1[i]=false;
            for(int j=0; j<m; ++j)
                scanf("%d", dfa1[i]+j);
        }
        scanf("%d", &n2);
        for(int i=0; i<n2; ++i)
        {
            scanf("%d", &t2);
            if(t2==1) d2[i]=true;
            else d2[i]=false;
            for(int j=0; j<m; ++j)
                scanf("%d", dfa2[i]+j);
        }
        printf("Case #%d: ", t1++);
        calculate();
    }
    return 0;
}

