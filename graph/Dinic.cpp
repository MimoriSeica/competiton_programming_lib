#include <bits/stdc++.h>

using namespace std;

#define REP(i,n) for(ll (i) = (0);(i) < (n);++i)
#define REV(i,n) for(ll (i) = (n) - 1;(i) >= 0;--i)
#define PB push_back
#define EB emplace_back
#define MP make_pair
#define FI first
#define SE second
#define SHOW1d(v,n) {REP(WW,n)cerr << v[WW] << ' ';cerr << endl << endl;}
#define SHOW2d(v,WW,HH) {REP(W_,WW){REP(H_,HH)cerr << v[W_][H_] << ' ';cerr << endl;}cerr << endl;}
#define ALL(v) v.begin(),v.end()
#define Decimal fixed<<setprecision(20)
#define INF 1000000000
#define LLINF 1000000000000000000LL
#define MOD 998244353

typedef long long ll;
typedef pair<ll,ll> P;

struct Dinic {
	struct edge{int to;long long cap,rev;};
	vector<vector<edge>> G;
	vector<int> level;
	vector<int> iter;

	Dinic(int n):G(n, vector<edge>()),level(n),iter(n){}

	void add_edge(int from,int to,long long cap){
		G[from].push_back((edge){to,cap,(ll)G[to].size()});
		G[to].push_back((edge){from,0,(ll)G[from].size()-1});
	}

	void bfs(int s){
		fill(level.begin(), level.end(), -1);
		queue<int> que;
		level[s] = 0;
		que.push(s);
		while(!que.empty())	{
			int v = que.front();que.pop();
			for(int i = 0;i < G[v].size();++i){
				edge &e = G[v][i];
				if(e.cap > 0 && level[e.to] < 0){
					level[e.to] = level[v] + 1;
					que.push(e.to);
				}
			}
		}
	}

	int dfs(int v ,int t,long long f){
		if(v == t)return f;
		for(int &i = iter[v];i < G[v].size() ;++i){
			edge &e = G[v][i];
			if(e.cap > 0 && level[v] < level[e.to]){
				long long d = dfs(e.to,t,min(f,e.cap));
				if(d > 0){
					e.cap -= d;
					G[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}

	long long solve(int s,int t){
		long long flow = 0;
		while(1){
			bfs(s);
			if(level[t] < 0)return flow;
			fill(iter.begin(), iter.end(), 0);
			long long f;while((f = dfs(s,t,INF)) > 0)flow += f;
		}
	}
};

int main() {
	int v, e;cin >> v >> e;
	Dinic dinic(v + 1);

	REP(i, e){
		ll a, b, c;cin >> a >> b >> c;
		dinic.add_edge(a, b, c);
	}

	cout << dinic.solve(0, v - 1) << endl;
}
