#include <iostream>
using namespace std;

int n, m, a, b;
bool know[100][100], removed[100];

void calculate()
{
    int ans=n;
    for(int i=0; i<n; ++i) removed[i]=false;
    while(true)
    {
        bool c=false;
        for(int i=0; i<n; ++i)
            if(!removed[i])
            {
                int k1=0, k2=0;
                for(int j=0; j<n; ++j)
                    if(j!=i&&know[i][j]&&!removed[j]) ++k1;
                    else if(j!=i&&!know[i][j]&&!removed[j]) ++k2;
                if(k1<a||k2<b)
                {
                    removed[i]=true;
                    --ans;
                    c=true;
                }
            }
        if(!c) break;
    }
    cout<<ans<<endl;
}

int main()
{
    int t=1;
    while(cin>>n>>m>>a>>b, n)
    {
        for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) know[i][j]=false;
        for(int i=0; i<m; ++i)
        {
            int t1, t2;
            cin>>t1>>t2;
            know[t1][t2]=know[t2][t1]=true;
        }
        cout<<"Case #"<<t++<<": ";
        calculate();
    }
    return 0;
}

