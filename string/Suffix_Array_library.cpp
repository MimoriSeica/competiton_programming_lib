#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG_MODE
	#define DBG(n) n;
#else
	#define DBG(n) ;
#endif
#define REP(i,n) for(ll (i) = (0);(i) < (n);++i)
#define PB push_back
#define MP make_pair
#define FI first
#define SE second
#define SHOW1d(v,n) {for(int W = 0;W < (n);W++)cerr << v[W] << ' ';cerr << endl << endl;}
#define SHOW2d(v,i,j) {for(int aaa = 0;aaa < i;aaa++){for(int bbb = 0;bbb < j;bbb++)cerr << v[aaa][bbb] << ' ';cerr << endl;}cerr << endl;}
#define ALL(v) v.begin(),v.end()
#define Decimal fixed<<setprecision(20)
#define INF 1000000000
#define LLINF 1000000000000000000
#define MOD 1000000007

typedef long long ll;
typedef pair<ll,ll> P;
struct SuffixArray {

	int n,k;
	string S;
	vector<int> rnk,tmp,sa,lcp;

	SuffixArray(string s){
		S = s;
		n = s.size();
		rnk.resize(n+1);
		tmp.resize(n+1);
		sa.resize(n+1);
		lcp.resize(n+1);
		construct_sa();
		construct_lcp();
	}

	void construct_sa(){

		for(int i = 0; i <= n;i++){
			sa[i] = i;
			rnk[i] = i < n ? S[i] : -1;
		}

		auto comp = [&](int &i, int &j){
			if(rnk[i] != rnk[j]){
				return rnk[i] < rnk[j];
			}
			else{
				int ri =( i + k <= n )? rnk[i + k] : -1;
				int rj =( j + k <= n )? rnk[j + k] : -1;
				return ri < rj;
			}
		};

		for(k = 1;k <= n ; k *= 2){
			sort(sa.begin(), sa.end(), comp);

			tmp[sa[0]] = 0;
			for(int i = 1; i <= n; i++)	{
				tmp[sa[i]] = tmp[sa[i -1]] + (comp(sa[i - 1],sa[i]) ? 1 : 0);
			}
			for(int i = 0;i <= n;i++){
				rnk[i] = tmp[i];
			}
		}
	}

	bool contain(string t){
		int a = 0,b = S.length();
		while(b - a > 1){
			int c = (a + b) / 2;

			if(S.compare(sa[c],t.length(),t) < 0) a = c;
			else b = c;
		}

		return (S.compare(sa[b], t.length(),t) == 0);
	}

	void construct_lcp(){
		int n = S.length();
		for(int i = 0;i <= n;i++)rnk[sa[i]] = i;

		int h = 0;
		lcp[0] = 0;
		for(int i = 0;i < n;i++){
			int j = sa[rnk[i] - 1];

			if(h > 0)h--;
			for(;j + h < n && i + h < n;h++){
				if(S[j + h] != S[i + h])break;
			}
			lcp[rnk[i] - 1] = h;
		}
	}
};

int main()
{
	string S;
	int N;

	cin >> S;
	cin >> N;
	SuffixArray sa(S);

	for(int i = 0 ;i < N;i++)
	{
		string T;
		cin >> T;
		if(sa.contain(T)) cout << 1 << endl;
		else cout << 0 << endl;
	}

	return 0;
}
