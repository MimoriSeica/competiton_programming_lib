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

typedef long long ll;
typedef pair<ll,ll> P;

#define BIT_N 2002
typedef bitset<BIT_N> Bit;

int Gaussian_elimination(vector<Bit> &v){
    int rank = 0;
    REP(i, BIT_N) {
        int pla = -1;
        for(int j = rank;j < v.size();j++){
            if(v[j][i] == 1){
                pla = j;
                break;
            }
        }

        if(pla != -1){
            swap(v[rank], v[pla]);
            for(int j = 0;j < v.size();j++){
                if(j == rank)continue;
                if(v[j][i] == 1)v[j] ^= v[rank];
            }
            rank++;
        }
    }
    return rank;
}

int Gaussian_elimination(vector<ll> &v){
	int rank = 0;
	REP(i, 60){
		int pla = -1;
		for(int j = rank;j < v.size();j++){
			if(v[j] & (1LL << i)){
				pla = j;
				break;
			}
		}
		if(pla != -1){
			swap(v[rank], v[pla]);
			REP(j,v.size()){
				if(j == rank)continue;
				if(v[j] & (1LL << i))v[j] ^= v[rank];
			}
			rank++;
		}
	}
    return rank;
}

int main(){
    return 0;
}
