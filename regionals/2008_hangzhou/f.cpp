#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
#define EPS 1e-7
int n, k, ra[5000], aa[15000], p[5000];
struct Point{int x; int y;}point[5000];
double r[15000], a[15000];
bool used[15000];
double pi=acos(-1.0);
double queue[10000];
int front, rear;

bool cmp1(int i, int j){return r[i]<r[j];}
bool cmp2(int i, int j){return a[i]<a[j];/*||a[i]==a[j]&&r[i]<r[j];*/}

void init()
{
    int x, y;
    for(int i=0; i<n; ++i)
    {
        x=point[i].x;
        y=point[i].y;
        r[i]=sqrt(x*x+y*y);
        if(y==0&&x>0) a[i]=0;
        else if(y==0&&x<0) a[i]=pi;
        else if(x==0&&y>0) a[i]=pi/2.0;
        else if(x==0&&y<0) a[i]=pi*1.5;
        else
        {
            a[i]=atan2(y*1.0, x*1.0);
            if(a[i]<0) a[i]+=pi*2.0;
        }
        ra[i]=aa[i]=i;
        used[i]=false;
    }
    sort(ra, ra+n, cmp1);
    sort(aa, aa+n, cmp2);
    for(int i=n; i<2*n; ++i) {aa[i]=aa[i-n]; p[aa[i]]=i;}
    for(int i=2*n; i<3*n; ++i) {aa[i]=aa[i-n];}
}

void calculate()
{
    double minimum=-1.0;
    for(int i=n-1; i+1>=k; --i)
    {
        double cost=r[ra[i]]*r[ra[i]]/2.0;
        double alpha=0.0;
        used[ra[i]]=true;
        front=0;
        rear=k;
        queue[k-1]=a[ra[i]];
        for(int j=p[ra[i]], l=k-2; l>=0; --j)
        {
            if(used[aa[j]]) continue;
            queue[l]=a[aa[j]];
            if(j<n) queue[l]-=pi*2;
            if(j>=2*n) queue[l]+=pi*2;
            --l;
        }
        alpha=queue[rear-1]-queue[front];
        if(alpha<0.0) alpha+=2*pi;
        for(int j=p[ra[i]], l=0; l<k-1; ++j)
        {
            if(used[aa[j]]) continue;
            queue[rear]=a[aa[j]];
            if(j<n) queue[rear]-=pi*2;
            if(j>=2*n) queue[rear]+=pi*2;
            ++front;
            ++rear;
            double t=queue[rear-1]-queue[front];
            if(t<0.0) t+=2*pi;
            if(t<alpha) alpha=t;
            ++l;
        }
        cost=cost*alpha;
        if(minimum<0.0||cost<minimum) minimum=cost;
    }
    printf("%.2lf\n", minimum);
}

int main()
{
    int t=1;
    while(scanf("%d %d", &n, &k), n)
    {
        printf("Case #%d: ", t++);
        for(int i=0; i<n; ++i) scanf("%d %d", &(point[i].x), &(point[i].y));
        if(k==0||k==1) {printf("0.00\n"); continue;}
        init();
        calculate();
    }
    return 0;
}

