#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char s[1000001];
int z[10000001];

void cal()
{
	int i=1, l=0, r=0;
	for(; s[i]; ++i)
		if(r<i)
		{
			int j=0, k=i;
			for(; s[j]==s[k]; ++j, ++k)
				;
			z[i]=j;
			l=i;
			r=k-1;
		}
		else
		{
			if(z[i-l]<r-i+1)
				z[i]=z[i-l];
			else
			{
				int j=r-i+1, k=r+1;
				for(; s[j]==s[k]; ++j, ++k)
					;
				z[i]=j;
				l=i;
				r=k-1;
			}
		}
	z[0]=i;
	//for(int i=0; s[i]; ++i)
	//	cout<<z[i]<<endl;
}

int main()
{
	int numOfCases, numOfQueries, p, l;
	scanf("%d", &numOfCases);
	while(numOfCases--)
	{
		scanf("%s", s);
		l=strlen(s);
		for(int i=0, j=l-1; i<j; ++i, --j)
		{
			char t=s[i];
			s[i]=s[j];
			s[j]=t;
		}
		cal();
		scanf("%d", &numOfQueries);
		while(numOfQueries--)
		{
			scanf("%d", &p);
			printf("%d\n", z[l-p]);
		}
	}
	return 0;
}

