#include <iostream>
#include <algorithm>
using namespace std;
int n, ma, mb, ia, ib, da, db, mapping[8];
bool ga[8][8], gb[8][8], gc[8][8];

void calculate()
{
    int minimum=-1, cost=0;
    for(int i=0; i<n; ++i) mapping[i]=i;
    do
    {
        for(int i=0; i<n; ++i)
            for(int j=0; j<n; ++j)
                gc[mapping[i]][mapping[j]]=gb[i][j];
        cost=0;
        for(int i=0; i<n; ++i)
            for(int j=i+1; j<n; ++j)
                if(ga[i][j]&&!gc[i][j])
                    cost=cost+(da<ib?da:ib);
                else if(!ga[i][j]&&gc[i][j])
                    cost=cost+(ia<db?ia:db);
        if(minimum==-1||minimum>cost) minimum=cost;
    }
    while(next_permutation(mapping, mapping+n));
    cout<<minimum<<endl;
}

int main()
{
    int a, b, t=1;
    while(cin>>n>>ma>>mb, n)
    {
        cin>>ia>>ib>>da>>db;
        for(int i=0; i<n; ++i)
            for(int j=0; j<n; ++j)
                ga[i][j]=gb[i][j]=false;
        for(int i=0; i<ma; ++i)
        {
            cin>>a>>b;
            ga[a][b]=ga[b][a]=true;
        }
        for(int i=0; i<mb; ++i)
        {
            cin>>a>>b;
            gb[a][b]=gb[b][a]=true;
        }
        cout<<"Case #"<<t++<<": ";
        calculate();
    }
    return 0;
}

