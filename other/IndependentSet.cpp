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

//0 start
//40頂点までの最大独立点集合を求める
struct IndependentSet {
	
	vector<pair<int,int> > v;
	vector<int> dp;
	vector<int> okaa;
	vector<int> okbb;
	vector<int> okba;
	int n;
	
	IndependentSet(int _n):dp(1<<(_n+1)/2),okaa((_n+1)/2),okbb((_n+1)/2),okba((_n+1)/2){
		n = _n;
	}
	
	void addEdge(int a,int b){
		v.EB(a, b);
	}
		
	int solve(){
		int Sa = n/2;
		int Sb = n - Sa;
		//initialize
		REP(i,Sa){
			okaa[i] = (1 << Sa) - 1;
		}
		REP(i,Sb){
			okbb[i] = (1 << Sb) - 1;
			okba[i] = (1 << Sa) - 1;
		}
		
		REP(q,v.size()){
			int a = min(v[q].FI,v[q].SE);
			int b = max(v[q].FI,v[q].SE);
			if(b < Sa){
				okaa[a] &= ~(1 << b);
				okaa[b] &= ~(1 << a);
			}
			else if(a < Sa){
				okba[b-Sa] &= ~(1 << a);
			}
			else{
				okbb[a-Sa] &= ~(1 << (b-Sa));
				okbb[b-Sa] &= ~(1 << (a-Sa));
			}
		}
		
		REP(q,(1<<Sa)){
			int now = q;
			int num = 0;
			REP(i,Sa){
				if(q & (1 << i)){now &= okaa[i];num++;}
			}
			if(now != q)continue;
			dp[q] = num;
		}
		
		REP(i,(1<<Sa)){
			REP(j,Sa){
				dp[i|(1<<j)] = max(dp[i],dp[i|(1<<j)]);
			}
		}
		
		int ret = 0;
		REP(q,(1<<Sb)){
			int node = q;
			int now = 0;
			REP(i,Sb){
				if(q & (1<<i)){node &= okbb[i];now++;}
			}
			if(node!=q)continue;
			
			int aa = (1<<Sa)-1;
			REP(i,Sb)
			{
				if(q & (1<<i))aa &= okba[i];
			}
			ret = max(ret,now+dp[aa]);
		}
		
		return ret;
	}
	
};

int main(){
	int n,m;
	cin >> n >> m;
	IndependentSet seica(n);
	REP(i,m){
		int a,b;cin >> a >> b;
		seica.addEdge(a-1, b-1);
	}
	
	cout << seica.solve() << endl;
	
	return 0;
}