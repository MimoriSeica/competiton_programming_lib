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
#define SHOW1d(v,n) {for(int W = 0;W < (n);W++)cerr << v[W] << ' ';cerr << endl << endl;}
#define SHOW2d(v,i,j) {for(int aaa = 0;aaa < i;aaa++){for(int bbb = 0;bbb < j;bbb++)cerr << v[aaa][bbb] << ' ';cerr << endl;}cerr << endl;}
#define ALL(v) v.begin(),v.end()
#define Decimal fixed<<setprecision(20)
#define INF 1000000000
#define MOD 1000000007

template< int mod, int primitiveroot >
struct NumberTheoreticTransform {
  vector< vector< int > > rts, rrts;
  void ensure_base(int N) {
    if(rts.size() >= N) return;
    rts.resize(N), rrts.resize(N);
    for(int i = 1; i < N; i <<= 1) {
      if(rts[i].size()) continue;
      int w = mod_pow(primitiveroot, (mod - 1) / (i * 2));
      int rw = inverse(w);
      rts[i].resize(i), rrts[i].resize(i);
      rts[i][0] = 1, rrts[i][0] = 1;
      for(int k = 1; k < i; k++) {
        rts[i][k] = mul(rts[i][k - 1], w);
        rrts[i][k] = mul(rrts[i][k - 1], rw);
      }
    }
  }

  inline int mod_pow(int x, int n) {
    int ret = 1;
    while(n > 0) {
      if(n & 1) ret = mul(ret, x);
      x = mul(x, x);
      n >>= 1;
    }
    return ret;
  }

  inline int inverse(int x) {
    return mod_pow(x, mod - 2);
  }

  inline int add(int x, int y) {
    x += y;
    if(x >= mod) x -= mod;
    return x;
  }

  inline int mul(int a, int b) {
    return int(1LL * a * b % mod);
  }

  void DiscreteFourierTransform(vector< int > &F, bool rev) {
    const int N = (int) F.size();
    ensure_base(N);
    for(int i = 0, j = 1; j + 1 < N; j++) {
      for(int k = N >> 1; k > (i ^= k); k >>= 1);
      if(i > j) swap(F[i], F[j]);
    }
    for(int i = 1; i < N; i <<= 1) {
      for(int j = 0; j < N; j += i * 2) {
        for(int k = 0; k < i; k++) {
          int s = F[j + k], t = mul(F[j + k + i], rev ? rrts[i][k] : rts[i][k]);
          F[j + k] = add(s, t), F[j + k + i] = add(s, mod - t);
        }
      }
    }
    if(rev) {
      int temp = inverse(N);
      for(int i = 0; i < N; i++) F[i] = mul(F[i], temp);
    }
  }

  vector< int > Multiply(const vector< int > &A, const vector< int > &B) {
    int sz = 1;
    while(sz < A.size() + B.size() - 1) sz <<= 1;
    vector< int > F(sz), G(sz);
    for(int i = 0; i < A.size(); i++) F[i] = A[i];
    for(int i = 0; i < B.size(); i++) G[i] = B[i];
    DiscreteFourierTransform(F, false);
    DiscreteFourierTransform(G, false);
    for(int i = 0; i < sz; i++) F[i] = mul(F[i], G[i]);
    DiscreteFourierTransform(F, true);
    F.resize(A.size() + B.size() - 1);
    return F;
  }
};


int main() {
  int N;
  scanf("%d", &N);
  vector< int > A(N + 1), B(N + 1);
  for(int i = 0; i < N; i++) scanf("%d %d", &A[i + 1], &B[i + 1]);
  NumberTheoreticTransform< 924844033,5 > ntt;
  auto C = ntt.Multiply(A, B);
  for(int i = 1; i <= 2 * N; i++) printf("%d\n", C[i]);
}
