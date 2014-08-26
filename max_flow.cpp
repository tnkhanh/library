#include <bits/stdc++.h>

#define PB push_back
#define MP make_pair
#define FI first
#define SE second

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 100005, INF = 2 * (int)1e9;

class MaxFlow{
    public:
    int n;
    vector<pii> adj[MAXN];
    vector<int> cap[MAXN], f[MAXN];
    int trace[MAXN];

    MaxFlow(int n_){
        n = n_;
    }
    
    void add(int x, int y, int c){ //use this to add edge x->y cost c
        int xs = adj[x].size(), ys = adj[y].size();
        
        adj[x].PB(MP(y, ys));
        cap[x].PB(c);
        f[x].PB(0);
        
        adj[y].PB(MP(x, xs));
        cap[y].PB(0);
        f[y].PB(0);
    }

    bool findpath(int s, int t){
	    memset(trace, 0xFF, sizeof trace);
	
	    int q[MAXN], front = 0, rear = 0;
	    q[0] = s;
	    trace[s] = 0;
	
	    while (front<=rear){
		    int x = q[front];
		    front++;
		
		    for (int i=0; i<adj[x].size(); i++){
			    int y = adj[x][i].FI;
			    if (trace[y]>-1) continue;
			    if (f[x][i]<cap[x][i]){
				    q[++rear] = y;
				    trace[y] = adj[x][i].SE;
        			if (y==t) return true;				
			    }						
		    }
	    }
	
	    return false;
    }

    int maxflow(int s, int t){ // use this to find maximum flow from s -> t; the result flow is found in adj[] and f[]
	    int res = 0;
	
	    while (findpath(s, t)){
		    int k = t, inc = INF;
		
		    while (k!=s){
			    int pk = trace[k], u = adj[k][pk].FI, 
				    pu = adj[k][pk].SE;

			    inc = min(inc, cap[u][pu] - f[u][pu]);
			    k = u;			
		    }
		
		    k = t;
		    while (k!=s){
			    int pk = trace[k], u = adj[k][pk].FI, 
				    pu = adj[k][pk].SE;
				
			    f[u][pu] += inc;
			    f[k][pk] -= inc;
			    k = u;
		    }
		
		    res += inc;
	    }
	
	    return res;
    }
};

int main(){
    int n;
    scanf("%d",&n);
    MaxFlow g(n);
     
    int u,v,cc;
    while (scanf("%d%d%d",&u,&v,&cc)!=EOF){
        g.add(u, v, cc);
    }
     
    printf("%d\n", g.maxflow(n, 1));
    return 0;
}
