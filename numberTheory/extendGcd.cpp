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
#define LLINF 1000000000000000000LL
#define MOD 1000000007

typedef long long ll;
typedef pair<ll,ll> P;

// ax + by = gcd(a, b)
long long extGcd(long long a, long long b, long long &x, long long &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long d = extGcd(b, a%b, y, x);
    y -= a / b * x;
    return d;
}

// aで割った余りがx、bで割った余りがyの時の、abで割った余り
// aとbは互いに素
long long CRT(long long a, long long b, long long x, long long y) {
    long long c, d;
    extGcd(a, b, c, b);
    ll ret = (a * y % (a * b) * c % (a * b) + (a * b)) % (a * b);
    return (ret + b * x  % (a * b)* d % (a * b) + (a * b)) % (a * b);
}


int main(){

    ll x, y;
    ll out = extGcd(111, 30, x , y);
    cout << x << " " << y << " " << 111 * x + 30 * y << " " << out << endl;

	return 0;
}
