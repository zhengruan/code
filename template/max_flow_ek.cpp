class EK
{
public:
	static const int V=1100, E=10000;
	static int n, m, s, t;
	static struct Edge{int from; int to; int v; int next;}net[E], rnet[E*2];
	static int head[V], rhead[V], q[V], qm[V], pre[V], front, rear;
	static bool visited[V];
	static int ek()
	{
		int flow=0, d=0, a, b;
		for(int i=0; i<n; ++i) rhead[i]=-1;
		for(int i=0; i<m; ++i)
		{
			a=net[i].from; b=net[i].to;
			rnet[i]=net[i];
			rnet[i].next=rhead[a];
			rhead[a]=i;
			rnet[i+m].from=b;
			rnet[i+m].to=a;
			rnet[i+m].v=0;
			rnet[i+m].next=rhead[b];
			rhead[b]=i+m;
		}
		while(d=augment())
			flow+=d;
		return flow;
	}
	static int augment()
	{
		if(s==t) return 0;
		static const int INF=-1;
		for(int i=0; i<n; ++i) visited[i]=false;
		q[0]=s; qm[0]=INF; pre[s]=-1; visited[s]=true; front=0; rear=1;
		while(front!=rear)
		{
			int a=q[front], b, d=qm[front];
			if(a==t)
			{
				for(int i=pre[t]; i!=-1; i=pre[rnet[i].from])
				{
					if(i<m) {rnet[i].v-=d; rnet[i+m].v+=d;}
					else {rnet[i].v-=d; rnet[i-m].v+=d;}
				}
				return d;
			}
			for(int i=rhead[a]; i!=-1; i=rnet[i].next)
			{
				b=rnet[i].to;
				if(!visited[b]&&rnet[i].v)
				{
					visited[b]=true;
					q[rear]=b;
					pre[b]=i;
					qm[rear]=rnet[i].v;
					if(qm[front]!=INF&&qm[rear]>qm[front]) qm[rear]=qm[front];
					++rear;
				}
			}
			++front;
		}
		return 0;
	}
};
int EK::n, EK::m, EK::s, EK::t;
struct EK::Edge EK::net[EK::E], EK::rnet[EK::E*2];
int EK::head[EK::V], EK::rhead[EK::V], EK::q[EK::V], EK::qm[EK::V], EK::pre[EK::V], EK::front, EK::rear;
bool EK::visited[EK::V];
