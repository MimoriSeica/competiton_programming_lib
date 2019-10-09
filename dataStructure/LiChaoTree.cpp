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

template<typename T>
struct LiChaoTree {

    vector<pair<T, T>> dat;
    vector<ll> x;
    pair<T, T> inf;
    int n;

    LiChaoTree(int n_, pair<T, T> inf_) {
        n = 1;
        while(n < n_ + 1)n *= 2;
        inf = inf_;

        dat = vector<pair<T, T>>(2 * n, inf);
        x = vector<ll>(n + 1);
        REP(i, x.size())x[i] = i;
    }

    LiChaoTree(vector<ll> coordinate, pair<T, T> inf_) {
        n = 1;
        while(n < coordinate.size() + 1)n *= 2;
        inf = inf_;

        dat = vector<pair<T, T>>(2 * n, inf);
        x = vector<ll>(n + 1);
		REP(i, x.size()){
            if(i < coordinate.size())x[i] = coordinate[i];
            else x[i] = x[i-1] + 1;
        }
    }

    T func(pair<T, T> line, int a){
        return line.first * a + line.second;
    }

    void add_line(pair<T, T> line, int k, int l, int r) {
        int m = (l + r) / 2;
        T lx = x[l];
        T mx = x[m];
        T rx = x[r];
        bool left = (func(line, lx) < func(dat[k], lx));
        bool mid = (func(line, mx) < func(dat[k], mx));
        bool right = (func(line, rx) < func(dat[k], rx));

        if(!left && !right){
            return;
        }
        if(mid){
            swap(line, dat[k]);
        }
        if(left != mid && 2*k+1 < dat.size()){
            add_line(line, 2*k+1, l, m);
        }
        else if(right != mid && 2*k+2 < dat.size()){
            add_line(line, 2*k+2, m, r);
        }
    }

    // [a, b) に線分を追加
    void add_line(pair<T, T> line, int a, int b) {
        int A = a + n - 1;
        int B = b + n - 1;
        int sz = 1;
        int al = a;
        int bl = b;
        while(A < B){
            if((A & 1) == 0){
                add_line(line, A++, al, al+sz);
                al += sz;
            }
            if((B & 1) == 0){
                bl -= sz;
                add_line(line, --B, bl, bl+sz);
            }
            A = A >> 1;
            B = B >> 1;
            sz = sz << 1;
        }
    }
    
    // 直線を追加
    void add_line(pair<T, T> line){
        add_line(line, 0, 0, n);
    }

    T query(int a){
        int ax = x[a];
        a += n - 1;
        T ans = func(dat[a], ax);
        while(a > 0){
            a = (a - 1) / 2;
            ans = min(ans, func(dat[a], ax));
        }
        return ans;
    }

};

int main(){
	cin.tie(0);cout.tie(0);ios::sync_with_stdio(false);

	return 0;
}
