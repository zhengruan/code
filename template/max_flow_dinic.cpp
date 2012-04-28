class Dinic
{
public:
	static const int V=40002, E=1000000;
	static int n, m, s, t;
	static struct Edge{int from; int to; int v; int next;}net[E], rnet[E*2];
	static int head[V], rhead[V], q[V], l[V], front, rear, top;
	static struct Node{int node; int pre; int next; int minimum; int where;}stack[V];
	static bool visited[V];
	static int dinic()
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
		int a, b, c, d=0;
		for(int i=0; i<n; ++i) {visited[i]=false; l[i]=INF;}
		l[s]=0; visited[s]=true; q[0]=s; front=0; rear=1;
		while(front!=rear)
		{
			a=q[front];
			if(a==t) {break;}
			for(int i=rhead[a]; i!=-1; i=rnet[i].next)
			{
				b=rnet[i].to;
				if(!visited[b]&&rnet[i].v) {visited[b]=true; q[rear]=b; l[b]=l[a]+1; ++rear; if(b==t) break;}
			}
			++front;
		}
		if(l[t]==INF) return 0;
		top=0;
		stack[0].node=s; stack[0].pre=INF; stack[0].next=rhead[s]; stack[0].minimum=INF; stack[0].where=INF;
		while(top!=-1)
		{
			a=stack[top].node;
			if(a==t)
			{
				c=stack[top].minimum;
				b=rnet[stack[top].where].from;
				d+=c;
				for(int i=0; i<top; ++i)
				{
					rnet[stack[i].pre].v-=c;
					stack[i+1].minimum-=c;
					if(stack[i].pre<m) rnet[stack[i].pre+m].v+=c;
					else rnet[stack[i].pre-m].v+=c;
				}
				while(stack[top].node!=b)
					--top;
			}
			else
			{
				if(stack[top].next==-1){l[stack[top].node]=INF; --top; continue;}
				for(int i=stack[top].next; i!=-1; i=rnet[i].next)
				{
					b=rnet[i].to;
					stack[top].next=rnet[i].next;
					if(l[b]==l[a]+1&&rnet[i].v)
					{
						stack[top].pre=i;
						stack[++top].node=b;
						stack[top].pre=INF;
						stack[top].next=rhead[b];
						if(stack[top-1].minimum==INF||rnet[i].v<stack[top-1].minimum)
						{
							stack[top].minimum=rnet[i].v;
							stack[top].where=i;
						}
						else
						{
							stack[top].minimum=stack[top-1].minimum;
							stack[top].where=stack[top-1].where;
						}
						break;
					}
				}
			}
		}
		return d;
	}
};
int Dinic::n, Dinic::m, Dinic::s, Dinic::t;
struct Dinic::Edge Dinic::net[Dinic::E], Dinic::rnet[Dinic::E*2];
int Dinic::head[Dinic::V], Dinic::rhead[Dinic::V], Dinic::q[Dinic::V], Dinic::l[Dinic::V], Dinic::front, Dinic::rear, Dinic::top;
struct Dinic::Node Dinic::stack[Dinic::V];
bool Dinic::visited[Dinic::V];
