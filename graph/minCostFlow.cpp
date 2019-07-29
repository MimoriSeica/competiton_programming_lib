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
#define MOD 1000000007
#define fastcin() cin.tie(0);ios::sync_with_stdio(false)

typedef long long ll;
typedef pair<ll,ll> P;

class minCostFlow {

	struct edge { ll to, cap, cost, rev; };

	ll V;
	vector<vector<edge>> G;
	vector<ll> dist;
	vector<ll> prevv;
	vector<ll> preve;

public:

	minCostFlow(ll n): G(n), dist(n), prevv(n), preve(n), V(n){
	}

	void addEdge(ll from, ll to, ll cap, ll cost) {
		G[from].push_back((edge){to, cap, cost, (ll)G[to].size()});
		G[to].push_back((edge){from, 0, -cost, (ll)G[from].size() - 1});
	}

	ll solve(ll s, ll t, ll f) {
		ll ret = 0;
		while(f > 0) {
			fill(dist.begin(), dist.end(), LLINF);
			dist[s] = 0;
			bool update = true;
			while(update) {
				update = false;
				for(ll v = 0;v < V;v++) {
					if(dist[v] == LLINF)continue;
					for(ll i = 0;i < G[v].size();i++) {
						edge &e = G[v][i];
						if(e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
							dist[e.to] = dist[v] + e.cost;
							prevv[e.to] = v;
							preve[e.to] = i;
							update = true;
						}
					}
				}
			}
			if(dist[t] == LLINF) {
				return LLINF;//流せない
			}

			ll d = f;
			for(ll v = t;v != s;v = prevv[v]) {
				d = min(d, G[prevv[v]][preve[v]].cap);
			}
			f -= d;
			ret += d * dist[t];
			for(ll v = t;v != s;v = prevv[v]) {
				edge &e = G[prevv[v]][preve[v]];
				e.cap -= d;
				G[v][e.rev].cap += d;
			}
		}
		return ret;
	}

};

//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B
int main(){

	int v,e,f;cin >> v >> e >> f;
	minCostFlow mcf(v);

	REP(i,e) {
		int a,b,c,d;cin >> a >> b >> c >> d;
		mcf.addEdge(a, b , c, d);
	}

	cout << mcf.solve(0, v-1, f) << endl;

	return 0;
}
