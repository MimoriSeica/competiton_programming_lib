struct UF {
	vector<int> par; // 親のインデックスを記憶する配列
	vector<int> sz; // サイズを記憶する。
	// 初期化
	UF(int n):par(n),sz(n){
		for(int i = 0; i < n; i++){
			par[i] = i;sz[i] = 1;
		}
	}
	// 親を求める
	int find(int x) {
		if (par[x] == x) return x;
		else return par[x] = find(par[x]);
	}
	// xとyの属する集合を併合
	void unite(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return;
		if(sz[x] > sz[y])swap(x, y);
		par[x] = y;
		sz[y] += sz[x];
		// マージデクはここでやる(x -> y)
	}
	// xとyが同じ集合ならtrue
	bool same(int x, int y) { return find(x) == find(y); }
	// 素の集合のサイズを求める
	int size(int n){return sz[find(n)];}
};
