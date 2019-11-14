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

vector<int> z_algorithm(string s){
   int n = s.size();
   vector<int> ret(n);
   ret[0] = n;
   int i = 1, j = 0;
   while(i < s.size()){
       while(i+j < s.size() && s[j] == s[i+j])++j;
       ret[i] = j;
       if(j == 0){ ++i; continue; }
       int k = 1;
       while(i + k < s.size() && k + ret[k] < j)ret[i+k] = ret[k],++k;
       i += k; j -= k;
   }
   return ret;
}

int main(){
	cin.tie(0);cout.tie(0);ios::sync_with_stdio(false);

	return 0;
}
