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
struct matrix {
	size_t H, W;
	std::vector<type> mat;
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

	void swap_row(int a, int b) {
		for (int i = 0;i < W;i++) {
			swap(at(a, i), at(b, i));
		}
	}
	void swap_column(int a, int b) {
		for (int i = 0;i < H;i++) {
			swap(at(i, a), at(i, b));
		}
	}

	// 余因子
	matrix adjugate(const int r, const int c) {
		assert(!(r < 0 || c < 0 || r >= H || c >= W));
		matrix<type> ret(H-1, W-1);
		int nr = 0;
		for (int ir = 0;ir < H;ir++) {
			if(ir == r)continue;
			int nc = 0;
			for (int ic = 0;ic < W;ic++) {
				if(ic == c)continue;
				ret.at(nr, nc) = at(ir, ic);
				nc++;
			}
			nr++;
		}
		return ret;
	}
};

template<class type>
matrix<type> unit(int N) {
	matrix<type> ret(N);
	for (size_t i = 0; i < N; ++i) {
		ret.at(i, i) = type(1);
	}
	return ret;
}

// 掃き出し法
template<class type>
void gaussian_elimination(matrix<type> &mt) {
	int rank = 0;
	for (ll c = 0;c < mt.W;c++) {
		int pla = -1;
		for (ll r = rank;r < mt.H;r++) {
			if (abs(mt.at(r, c)) > 1e-8) {
				pla = r;
				break;
			}
		}

		if(pla == -1) continue;
		mt.swap_row(rank, pla);
		for (int r = 0;r < mt.H;r++) {
			if(r == rank)continue;
			type kake = mt.at(r, c) / mt.at(rank, c);
			for (int cc = 0;cc < mt.W;cc++) {
				mt.at(r, cc) -= kake * mt.at(rank, cc);
			}
		}
		rank++;
	}
}

// 行列式
template<class type>
type determinant(matrix<type> mt) {
	if(mt.H != mt.W)return -1;
	gaussian_elimination(mt);
	type det = 1;
	for (int i = 0;i < mt.H;i++) {
		det *= mt.at(i, i);
	}

	return det;
}

int main(){
	return 0;
}
