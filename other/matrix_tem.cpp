#include <bits/stdc++.h>

using namespace std;

#define REP(i,n) for(ll (i) = (0);(i) < (n);++i)
#define REV(i,n) for(ll (i) = (n) - 1;(i) >= 0;--i)
#define PB push_back
#define EB emplace_back
#define MP make_pair
#define FI first
#define SE second
#define SHOW1d(v,n) {REP(W,n)cerr << v[W] << ' ';cerr << endl << endl;}
#define SHOW2d(v,i,j) {REP(aaa,i){REP(bbb,j)cerr << v[aaa][bbb] << ' ';cerr << endl;}cerr << endl;}
#define ALL(v) v.begin(),v.end()
#define Decimal fixed<<setprecision(20)
#define INF 1000000000
#define LLINF 1000000000000000000LL
#define MOD 1000000007

typedef long long ll;
typedef pair<ll,ll> P;

template<class type>
class matrix {
private:
	size_t H, W;
	std::vector<type> mat;
public:
	matrix() : H(0), W(0), mat(std::vector<type>()) {};
	matrix(size_t N_) : H(N_), W(N_), mat(std::vector<type>(N_ * N_)) {};
	matrix(size_t H_, size_t W_) : H(H_), W(W_), mat(std::vector<type>(H_ * W_)) {};
	type& at(size_t r, size_t c) { return mat[r * W + c]; }
	type at(size_t r, size_t c) const { return mat[r * W + c]; }
	matrix& operator+=(const matrix& m) {
		assert(H == m.H && W == m.W);
		for (size_t i = 0; i < H; ++i) {
			for (size_t j = 0; j < W; ++j) {
				mat[i * W + j] += m.mat[i * W + j];
			}
		}
	}
	matrix& operator-=(const matrix& m) {
		assert(H == m.H && W == m.W);
		for (size_t i = 0; i < H; ++i) {
			for (size_t j = 0; j < W; ++j) {
				mat[i * W + j] -= m.mat[i * W + j];
			}
		}
	}
	matrix& operator*=(const matrix& m) {
		assert(W == m.H);
		matrix ans(H, m.W);
		for (size_t i = 0; i < H; ++i) {
			for (size_t j = 0; j < m.W; ++j) {
				for (size_t k = 0; k < W; ++k) {
					ans.mat[i * m.W + j] += mat[i * W + k] * m.mat[k * m.W + j];
				}
			}
		}
		return (*this) = ans;
	}
	matrix operator+(const matrix& m) const { return matrix(*this) += m; }
	matrix operator-(const matrix& m) const { return matrix(*this) -= m; }
	matrix operator*(const matrix& m) const { return matrix(*this) *= m; }
};

template<class type>
matrix<type> unit(int N) {
	matrix<type> ret(N);
	for (size_t i = 0; i < N; ++i) {
		ret.at(i, i) = type(1);
	}
	return ret;
}

int main(){
	return 0;
}
