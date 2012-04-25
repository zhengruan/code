#include <iostream>
#include <cstdio>
using namespace std;

int mapping[100000], n, m, f[2000000], size[2000000];

int find(int p)
{
    while(p!=f[p])
        p=f[p]=f[f[p]];
    return p;
}

int uni(int i, int j)
{
    int fi=find(i), fj=find(j);
    if(fi!=fj) {f[fi]=fj; size[fj]+=size[fi]; return 1;}
    return 0;
}

int main()
{
    char op[10]; int a, b, t=1;
    while(scanf("%d %d", &n, &m), n)
    {
        int ans=n, next=n;
        for(int i=0; i<n; ++i) {f[i]=mapping[i]=i; size[i]=1;}
        for(int i=0; i<m; ++i)
        {
            scanf("%s", op);
            if(op[0]=='M')
            {
                scanf("%d %d", &a, &b);
                int ret=uni(mapping[a], mapping[b]);
                ans=ans-ret;
            }
            else
            {
                scanf("%d", &a);
                --size[find(mapping[a])];
                if(size[find(mapping[a])]) ++ans;
                mapping[a]=next;
                f[next]=next;
                size[next]=1;
                ++next;
            }
        }
        printf("Case #%d: %d\n", t++, ans);
    }
    return 0;
}

