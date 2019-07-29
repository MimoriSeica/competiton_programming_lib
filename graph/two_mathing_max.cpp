#include <bits/stdc++.h>

using namespace std;

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

#define MAX_V 2222
vector<int> v[MAX_V];
int match[MAX_V];
bool used[MAX_V];

void add_edge(int a,int b){
	v[a].PB(b);
	v[b].PB(a);
}

bool matchdfs(int a){
	used[a] = true;
	for(int i = 0;i < v[a].size();i++)	{
		int u = v[a][i],w = match[u];
		if(w < 0 || !used[w] && matchdfs(w)){
			match[u] = a;
			match[a] = u;
			return true;
		}
	}
	return false;
}

//二部マッチング
int two_matching_max(int l){
	int res = 0;
	memset(match,-1,sizeof(match));
	REP(v,l){
		if(match[v] < 0){
			memset(used,0,sizeof(used));
			if(matchdfs(v))res++;
		}
	}
	return res;
}

int main(){
	return 0;
}
