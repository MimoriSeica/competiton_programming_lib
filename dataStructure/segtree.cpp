/*
0-index
functionの中を書いて使う
segtree<ll> seg(n, [](ll a, ll b){return a + b;}, 0);
*/
template<typename T>
struct segtree{
	int n;
	vector<T> dat;
	T ZERO;
	function<T(T,T)> func;//要素と要素をマージする関数

	segtree(int n_, function<T(T,T)> func_, T zero):func(func_), ZERO(zero){
	  n = 1;
	  while(n < n_)n*=2;
	  dat.resize(2*n);
	  for(int i = 0;i < 2*n;i++)dat[i] = ZERO;
	}

	void update(int k, T a){
	  k += n - 1;dat[k] = a;
	  while(k > 0){
		k = (k-1)/2;
		dat[k] = func(dat[k*2+1],dat[k*2+2]);
	  }
	}

	void set(int k, T a) {
		k += n - 1;dat[k] = a;
	}

	void build(){
		for(int i = n - 2;i >= 0;i--){
			dat[i] = func(dat[2 * i + 1], dat[2 * i + 2]);
		}
	}

	T get(int k){return dat[k+n-1];}

	T que(int a,int b){
		T L = ZERO,R = ZERO;
		int A = a + n - 1;
		int B = b + n - 1;
		while(A < B){
			if((A & 1) == 0)L = func(L,dat[A++]);
            if((B & 1) == 0)R = func(dat[--B],R);
            A = A >> 1;
            B = B >> 1;
		}
		return func(L,R);
	}
};
