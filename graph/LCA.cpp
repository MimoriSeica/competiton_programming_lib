#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG_MODE
	#define DBG(n) n;
#else
	#define DBG(n) ;
#endif
#define REP(i,n) for(ll (i) = (0);(i) < (n);++i)
#define rep(i,s,g) for(ll (i) = (s);(i) < (g);++i)
#define rrep(i,s,g) for(ll (i) = (s);i >= (g);--(i))
#define PB push_back
#define MP make_pair
#define FI first
#define SE second
#define SHOW1d(v,n) {for(int W = 0;W < (n);W++)cerr << v[W] << ' ';cerr << endl << endl;}
#define SHOW2d(v,i,j) {for(int aaa = 0;aaa < i;aaa++){for(int bbb = 0;bbb < j;bbb++)cerr << v[aaa][bbb] << ' ';cerr << endl;}cerr << endl;}
#define ALL(v) v.begin(),v.end()
#define Decimal fixed<<setprecision(20)
#define INF 1000000000
#define MOD 1000000007

typedef long long ll;
typedef pair<ll,ll> P;

struct UF{
	vector<int> par; // 親
	vector<int> sz; // 数
	// 初期化
	UF(int n):par(n),sz(n) {
		for(int i = 0; i < n; i++){
			par[i] = i;sz[i] = 1;
		}
	}
	// 木の根を求める
	int find(int x) {
		if (par[x] == x) return x;
		else return par[x] = find(par[x]);
	}
	// xとyの属する集合を併合
	void unite(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return;
		par[x] = y;
		sz[x] += sz[y];
	}
	// xとyが同じ集合ならtrue
	bool same(int x, int y) { return find(x) == find(y); }
	int size(int n){return sz[find(n)];}
};

//普通のLCA(UFと一緒に) 
struct LCA{
	//隣接リスト、(相手、重み)
	vector<vector<pair<int,int> > > g;
	//親
	vector<vector<int> > parent;
	//深さ
	vector<int> depth;
	UF uf;
	int sz;
	vector<bool> inited;
		
	LCA(int n):g(n),parent(20,vector<int>(n)),
	inited(n,false),depth(n),uf(n){sz = n;}
	
	//辺の追加(点、点、重み)
	void add_edge(int u,int v,int w = 1){
		if(uf.same(u,v))return;
		g[v].PB(MP(u,w));
		g[u].PB(MP(v,w));
		uf.unite(v,u);
	}
		
	void dfs(int v,int p,int d){
		inited[v] = true;
		parent[0][v] = p;
		depth[v] = d;
		REP(i,g[v].size()){
			if(g[v][i].FI != p)dfs(g[v][i].FI,v,d+1);
		}
	}
	
	void init(){
		REP(i,sz)if(!inited[i])dfs(uf.find(i),-1,0);
		REP(k,19){
			REP(i,sz){
				if(parent[k][i] < 0)parent[k+1][i] = -1;
				else parent[k+1][i] = parent[k][parent[k][i]];
			}
		}
	}
	
	int ret_lca(int a,int b){
		
		if(!uf.same(a,b))return -1;
		
		if(depth[a] > depth[b])swap(a,b);
		REP(k,20){
			if((depth[b] - depth[a])>>k&1)b = parent[k][b];
		}
		if(a == b)return a;
		
		for(int k = 19;k >= 0;k--){
			if(parent[k][a] != parent[k][b])
			{
				a = parent[k][a];
				b = parent[k][b];
			}
		}
		return parent[0][a];
	}
	
};

//任意の二点のパスの中の最大値を求められる。(UFと一緒に) 
struct LCA{
	//隣接リスト、(相手、重み)
	vector<vector<pair<int,int> > > g;
	//親
	vector<vector<int> > parent;
	vector<vector<int> > value;
	//深さ
	vector<int> depth;
	UF uf;
	int sz;
	vector<bool> inited;
	
	map<pair<int,int> ,int> mp;
	
	pair<int,int> Pair(int a,int b){
		return MP(min(a,b),max(a,b));
	}
	
	LCA(int n):g(n),parent(20,vector<int>(n)),
	inited(n,false),depth(n),uf(n),value(20,vector<int>(n)){sz = n;}
	
	//辺の追加(点、点、重み)
	void add_edge(int u,int v,int w = 1){
		if(uf.same(u,v))return;
		g[v].PB(MP(u,w));
		g[u].PB(MP(v,w));
		uf.unite(v,u);
		mp[Pair(u,v)] = w;
	}
		
	void dfs(int v,int p,int d){
		inited[v] = true;
		value[0][v] = mp[Pair(v,p)];
		parent[0][v] = p;
		depth[v] = d;
		REP(i,g[v].size())
		{
			if(g[v][i].FI != p)dfs(g[v][i].FI,v,d+1);
		}
	}
	
	//頂点の追加後、ここで構築する
	void init(){
		REP(i,sz)if(!inited[i])dfs(uf.find(i),-1,0);
		REP(k,19){
			REP(i,sz){
				if(parent[k][i] < 0){
					parent[k+1][i] = -1;
					value[k+1][i] = value[k][i];
				}
				else {
					parent[k+1][i] = parent[k][parent[k][i]];
					value[k+1][i] = max(value[k][i],value[k][parent[k][i]]);
				}
			}
		}
	}
	
	int ret_lca(int a,int b){
		
		if(!uf.same(a,b))return -1;
		
		if(depth[a] > depth[b])swap(a,b);
		REP(k,20){
			if((depth[b] - depth[a])>>k&1)b = parent[k][b];
		}
		if(a == b)return a;
		
		for(int k = 19;k >= 0;k--){
			if(parent[k][a] != parent[k][b]){
				a = parent[k][a];
				b = parent[k][b];
			}
		}
		return parent[0][a];
	}
	
	int ret_value(int a,int b){
		
		if(!uf.same(a,b))return -1;
		int ret = 0;
		if(depth[a] > depth[b])swap(a,b);
		REP(k,20){
			if((depth[b] - depth[a])>>k&1){
				ret = max(ret,value[k][b]);
				b = parent[k][b];
			}
		}
		if(a == b)return ret;
		
		for(int k = 19;k >= 0;k--){
			if(parent[k][a] != parent[k][b]){
				ret = max(ret,value[k][a]);
				ret = max(ret,value[k][b]);
				a = parent[k][a];
				b = parent[k][b];
			}
		}
		ret = max(ret,value[0][a]);
		ret = max(ret,value[0][b]);
		
		return ret;
	}
	
};

int main(){
	return 0;
}