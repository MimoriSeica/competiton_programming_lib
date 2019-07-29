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

struct FastFourierTransform {
  using C = complex< double >;

  const double PI = acos(-1);
  vector< vector< C > > rts, rrts;

  void ensure_base(int N) {
    if(rts.size() >= N) return;
    rts.resize(N), rrts.resize(N);
    for(int i = 1; i < N; i <<= 1) {
      if(rts[i].size()) continue;
      rts[i].resize(i), rrts[i].resize(i);
      for(int k = 0; k < i; k++) {
        rts[i][k] = polar(1.0, PI / i * k);
        rrts[i][k] = polar(1.0, -PI / i * k);
      }
    }
  }

  void DiscreteFourierTransform(vector< C > &F, bool rev) {
    const int N = (int) F.size();
    auto &r = rev ? rrts : rts;

    for(int i = 0, j = 1; j + 1 < N; j++) {
      for(int k = N >> 1; k > (i ^= k); k >>= 1);
      if(i > j) swap(F[i], F[j]);
    }
    ensure_base(N);
    C s, t;
    for(int i = 1; i < N; i <<= 1) {
      for(int j = 0; j < N; j += i * 2) {
        for(int k = 0; k < i; k++) {
          s = F[j + k];
          t = C(F[j + k + i].real() * r[i][k].real() - F[j + k + i].imag() * r[i][k].imag(),
                F[j + k + i].real() * r[i][k].imag() + F[j + k + i].imag() * r[i][k].real());
          F[j + k] = s + t, F[j + k + i] = s - t;
        }
      }
    }
    if(rev) for(int i = 0; i < N; i++) F[i] /= N;
  }

  vector< long long > Multiply(const vector< int > &A, const vector< int > &B) {
    int sz = 1;
    while(sz < A.size() + B.size() - 1) sz <<= 1;
    vector< C > F(sz), G(sz);
    for(int i = 0; i < A.size(); i++) F[i] = A[i];
    for(int i = 0; i < B.size(); i++) G[i] = B[i];
    DiscreteFourierTransform(F, false);
    DiscreteFourierTransform(G, false);
    for(int i = 0; i < sz; i++) F[i] *= G[i];
    DiscreteFourierTransform(F, true);
    vector< long long > X(A.size() + B.size() - 1);
    for(int i = 0; i < A.size() + B.size() - 1; i++) X[i] = F[i].real() + 0.5;
    return (X);
  }
};


int main() {
  int N;
  scanf("%d", &N);
  vector< int > A(N + 1), B(N + 1);
  for(int i = 0; i < N; i++) scanf("%d %d", &A[i + 1], &B[i + 1]);
  FastFourierTransform fft;
  auto C = fft.Multiply(A, B);
  for(int i = 1; i <= 2 * N; i++) printf("%lld\n", C[i]);
}
