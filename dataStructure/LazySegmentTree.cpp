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

template <typename T,typename E>
struct SegmentTree{
	typedef function<T(T,T)> F;
	typedef function<T(T,E)> G;
	typedef function<E(E,E)> H;
	typedef function<E(E,int)> P;
	int n;
	F f;
	G g;
	H h;
	P p;
	T d1;
	E d0;
	vector<T> dat;
	vector<E> laz;

	SegmentTree(int n_,
				F f,//要素と要素をマージする関数
				G g,//要素に作用素を作用させる関数
				H h,//作用素と作用素をマージする関数
				T d1,//要素のモノイド
				E d0,//作用素のモノイド
				vector<T> v=vector<T>(),
				P p=[](E a,int b){return a;})://区間に対する操作が要素数に比例して変化する場合
	f(f),g(g),h(h),d1(d1),d0(d0),p(p){
		init(n_);
		if(n_==(int)v.size()) build(n_,v);
	}
	
	void init(int n_){
		n=1;
		while(n<n_) n*=2;
		dat.clear();
		dat.resize(2*n-1,d1);
		laz.clear();
		laz.resize(2*n-1,d0);
	}
	
	void build(int n_, vector<T> v){
		for(int i=0;i<n_;i++) dat[i+n-1]=v[i];
		for(int i=n-2;i>=0;i--){
			dat[i]=f(dat[i*2+1],dat[i*2+2]);
		}
	}
	
	inline void eval(int len,int k){
		if(laz[k]==d0) return;
		if(k*2+1<n*2-1){
			laz[k*2+1]=h(laz[k*2+1],laz[k]);
			laz[k*2+2]=h(laz[k*2+2],laz[k]);
		}
		dat[k]=g(dat[k],p(laz[k],len));
		laz[k]=d0;
	}
	
	
	T update(int a,int b,E x,int k,int l,int r){
		eval(r-l,k);
		if(r<=a||b<=l) return dat[k];
		if(a<=l&&r<=b){
			laz[k]=h(laz[k],x);
			return g(dat[k],p(laz[k],r-l));
		}
		return dat[k]=f(update(a,b,x,k*2+1,l,(l+r)/2),
				update(a,b,x,k*2+2,(l+r)/2,r));
	}
	
	T update(int a,int b,E x){
		return update(a,b,x,0,0,n);
	}
	
	T query(int a,int b,int k,int l,int r){
		eval(r-l,k);
		if(r<=a||b<=l) return d1;
		if(a<=l&&r<=b) return dat[k];
		T vl=query(a,b,k*2+1,l,(l+r)/2);
		T vr=query(a,b,k*2+2,(l+r)/2,r);
		return f(vl,vr);
	}
	
	T query(int a,int b){
		return query(a,b,0,0,n);
	}
};
/**
	SegmentTree(int n_,
				F f,//要素と要素をマージする関数
				G g,//要素に作用素を作用させる関数
				H h,//作用素と作用素をマージする関数
				T d1,//要素のモノイド
				E d0,//作用素のモノイド
				vector<T> v=vector<T>(),//初期配列
				P p=[](E a,int b){return a;})://区間に対する操作が要素数に比例して変化する場合
				
	区間加算、区間和
	SegmentTree<ll,ll> seg(n,
	[](ll a,ll b){return a + b;},
	[](ll a,ll b){return a + b;},
	[](ll a,ll b){return a + b;},
	0,
	0,
	vector<ll>(n,0),
	[](ll a,int b){return a * b;});
	
	区間更新、区間最小
	SegmentTree<ll,ll> seg(n,
	[](ll a,ll b){return min(a, b);},
	[](ll a,ll b){return b;},
	[](ll a,ll b){return b;},
	INF,
	INF,
	vector<ll>(n,INF),
	[](ll a,int b){return a;});
	
	区間加算、区間最小
	
	SegmentTree<ll,ll> seg(n,
	[](ll a,ll b){return min(a, b);},
	[](ll a,ll b){return a + b;},
	[](ll a,ll b){return a + b;},
	INF,
	0,
	vector<ll>(n,0),
	[](ll a,int b){return a;});

	区間更新、区間和
	SegmentTree<ll,ll> seg(n,
	[](ll a,ll b){return a + b;},
	[](ll a,ll b){return b;},
	[](ll a,ll b){return b;},
	0,
	INF,
	vector<ll>(n,0),
	[](ll a,int b){return a * b;});
**/

int main(){
	
	return 0;
}
