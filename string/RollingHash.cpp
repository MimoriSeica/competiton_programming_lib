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
#define SHOW1d(v,n) {for(int WWW = 0;WWW < (n);WWW++)cerr << v[WWW] << ' ';cerr << endl << endl;}
#define SHOW2d(v,i,j) {for(int aaa = 0;aaa < i;aaa++){for(int bbb = 0;bbb < j;bbb++)cerr << v[aaa][bbb] << ' ';cerr << endl;}cerr << endl;}
#define ALL(v) v.begin(),v.end()
#define Decimal fixed<<setprecision(20)
#define INF 1000000000
#define LLINF 1000000000000000000LL

typedef long long ll;
typedef pair<ll,ll> P;

#define N 3
ll mod[] = {999999937,1000000007,1000000009};
ll kake = 123123;

ll m_pow(ll a,ll b,ll p){
	ll ret = 1;
	ll tmp = a;
	for(ll i = 0LL;i < 60;i++){
		if(b & (1LL << i)){
			ret *= tmp;
			ret %= p;
		}
		tmp *= tmp;
		tmp %= p;
	}
	return ret;
}

//strが元の文字列、sが探したい文字列、一致する頭のリストを返す、O(N+M)
vector<int> RollingHash(string str,string s){
	vector<int> ret;
	ll mark[N] = {};
	REP(i,s.size()){
		REP(j,N){
			mark[j] *= kake;
			mark[j] += (int)s[i];
			mark[j] %= mod[j];
		}
	}
	ll po[N];
	REP(i,N)po[i] = m_pow(kake,s.size()-1,mod[i]);
	ll now[N] = {};
	REP(i,str.size()){
		bool flag = true;
		REP(j,N){
			if(i >= s.size()){
				ll tmp = po[j] * (int)str[i-s.size()] % mod[j];
				now[j] = (now[j] + mod[j] - tmp) % mod[j];
			}
			now[j] *= kake;
			now[j] += (int)str[i];
			now[j] %= mod[j];
			if(now[j] != mark[j])flag = false;
		}
		if(flag)ret.PB(i-s.size()+1);
	}
	return ret;
}

int main(){
	
	string a,b;cin >> a >> b;
	vector<int> ans = RollingHash(a,b);
	REP(i,ans.size()){
		cout << ans[i] << endl;
	}
	
	return 0;
}
