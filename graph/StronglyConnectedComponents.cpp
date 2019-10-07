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


struct SCC {
	vector<vector<int>> G;
	vector<vector<int>> rG;
	vector<int> vs;
	vector<bool> used;
	vector<int> cmp;
	vector<int> sorted_num; // SCC 後のトポロジカルソートの順番が入る
	int sz,newsz;
	SCC(int n):G(n),rG(n),used(n,false),cmp(n){sz = n;}

	//辺を張る
	void add_edge(int from,int to){
		G[from].PB(to);
		rG[to].PB(from);
	}

	void dfs(int v){
		used[v] = true;
		REP(i,G[v].size()){
			if(!used[G[v][i]])dfs(G[v][i]);
		}
		vs.PB(v);
	}

	void rdfs(int v,int k){
		used[v] = false;
		cmp[v] = k;
		REP(i,rG[v].size()){
			if(used[rG[v][i]])rdfs(rG[v][i],k);
		}
	}

	//SCC実行
	int solve(){
		vs.clear();
		REP(i,sz)if(!used[i])dfs(i);
		int k = 0;
		for(int i = sz-1;i >= 0;i--){
			if(used[vs[i]]){
				rdfs(vs[i],k++);
			}
		}
		return newsz = k;
	}

	//SCC した後の頂点を返す
	int scc_node(int n){
		return cmp[n];
	}

	// 同じ頂点か
	bool isSameGroup(int a, int b){
		return cmp[a] == cmp[b];
	}

	// SCC 後のグラフのトポロジカルシート
	void topological_sort() {
		sorted_num.resize(newsz);
        vector<int> cou(newsz);
        vector<vector<int>> new_v(newsz);

        REP(i, sz){
            new_v[scc_node(i)].PB(i);
        }

        queue<int> q;
        REP(i, newsz){
            REP(j, new_v[i].size()){
                int node = new_v[i][j];
                REP(k, rG[node].size()){
                    int aite = rG[node][k];
                    if(isSameGroup(node, aite))continue;
                    cou[i]++;
                }
            }
            if(cou[i] == 0){
                q.push(i);
            }
        }

        int num = 0;
        while(!q.empty()){
            int now = q.front();q.pop();
            sorted_num[now] = num;
            num++;

            REP(i, new_v[now].size()){
                int node = new_v[now][i];
                REP(j, G[node].size()){
                    int aite = G[node][j];
                    if(isSameGroup(node, aite))continue;
                    cou[scc_node(aite)]--;

                    if(cou[scc_node(aite)] == 0){
                        q.push(scc_node(aite));
                    }
                }
            }
        }
	}

	// SCC 後のトポロジカル順序を返す
	int topological_order(int node){
		return sorted_num[cmp[node]];
	}
};

int main(){
	cin.tie(0);cout.tie(0);ios::sync_with_stdio(false);

	return 0;
}
