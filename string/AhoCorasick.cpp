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
#define fastcin() cin.tie(0);ios::sync_with_stdio(false)

typedef long long ll;
typedef pair<ll,ll> P;

template< int char_size >
struct TrieNode {
	int nxt[char_size + 1];

	int exist;
	vector< int > accept;

	TrieNode() : exist(0) {
		memset(nxt, -1, sizeof(nxt));
	}
};

template< int char_size, int margin >
struct Trie {
	using Node = TrieNode< char_size >;

	vector< Node > nodes;
	int root;

	Trie() : root(0) {
		nodes.push_back(Node());
	}

	void update_direct(int node, int id) {
		nodes[node].accept.push_back(id);
	}

	void update_child(int node, int child, int id) {
		++nodes[node].exist;
	}

	void add(const string &str, int str_index, int node_index, int id) {
		if(str_index == str.size()) {
			update_direct(node_index, id);
		} else {
			const int c = str[str_index] - margin;
			if(nodes[node_index].nxt[c] == -1) {
				nodes[node_index].nxt[c] = (int) nodes.size();
				nodes.push_back(Node());
			}
			add(str, str_index + 1, nodes[node_index].nxt[c], id);
			update_child(node_index, nodes[node_index].nxt[c], id);
		}
	}

	void add(const string &str, int id) {
		add(str, 0, 0, id);
	}

	void add(const string &str) {
		add(str, nodes[0].exist);
	}

	void query(const string &str, const function< void(int) > &f, int str_index, int node_index) {
		for(auto &idx : nodes[node_index].accept) f(idx);
		if(str_index == str.size()) {
			return;
		} else {
			const int c = str[str_index] - margin;
			if(nodes[node_index].nxt[c] == -1) return;
			query(str, f, str_index + 1, nodes[node_index].nxt[c]);
		}
	}

	void query(const string &str, const function< void(int) > &f) {
		query(str, f, 0, 0);
	}

	int size() const {
		return (nodes[0].exist);
	}

	int nodesize() const {
		return ((int) nodes.size());
	}
};


template< int char_size, int margin >
struct AhoCorasick : Trie< char_size, margin > {
	using TRIE = Trie< char_size, margin >;
	static const int FAIL = char_size;
	vector< int > correct;

	AhoCorasick() : TRIE() {}

	void build(bool heavy = true) {
		correct.resize(TRIE::nodes.size());
		for(int i = 0; i < TRIE::nodes.size(); i++) {
			correct[i] = (int) TRIE::nodes[i].accept.size();
		}

		queue< int > que;
		for(int i = 0; i <= char_size; i++) {
			if(~TRIE::nodes[0].nxt[i]) {
				TRIE::nodes[TRIE::nodes[0].nxt[i]].nxt[FAIL] = 0;
				que.emplace(TRIE::nodes[0].nxt[i]);
			} else {
				TRIE::nodes[0].nxt[i] = 0;
			}
		}
		while(!que.empty()) {
			TrieNode< char_size > &now = TRIE::nodes[que.front()];
			correct[que.front()] += correct[now.nxt[FAIL]];
			que.pop();
			for(int i = 0; i < char_size; i++) {
				if(now.nxt[i] == -1) continue;
				int fail = now.nxt[FAIL];
				while(TRIE::nodes[fail].nxt[i] == -1) fail = TRIE::nodes[fail].nxt[FAIL];
				TRIE::nodes[now.nxt[i]].nxt[FAIL] = TRIE::nodes[fail].nxt[i];
				if(heavy) {
					auto &u = TRIE::nodes[now.nxt[i]].accept;
					auto &v = TRIE::nodes[TRIE::nodes[fail].nxt[i]].accept;
					vector< int > accept;
					set_union(begin(u), end(u), begin(v), end(v), back_inserter(accept));
					u = accept;
				}
				que.emplace(now.nxt[i]);
			}

		}
	}

	int match(const string &str, vector< int > &result, int now = 0) {
		result.assign(TRIE::size(), 0);
		int count = 0;
		for(auto &c : str) {
			while(TRIE::nodes[now].nxt[c - margin] == -1) now = TRIE::nodes[now].nxt[FAIL];
			now = TRIE::nodes[now].nxt[c - margin];
			count += correct[now];
			for(auto &v : TRIE::nodes[now].accept) ++result[v];
		}
		return (count);
	}
	
	int match(const string &str, vector< vector< int > > &result, int now = 0) {
		result.assign(TRIE::size(), vector<int>());
		int count = 0;
		for(int i = 0;i < str.size();i++) {
			char c = str[i];
			while(TRIE::nodes[now].nxt[c - margin] == -1) now = TRIE::nodes[now].nxt[FAIL];
			now = TRIE::nodes[now].nxt[c - margin];
			count += correct[now];
			for(auto &v : TRIE::nodes[now].accept) result[v].PB(i);
		}
		return (count);
	}

	int move(const char &c, int &now) {
		int count = 0;
		while(TRIE::nodes[now].nxt[c - margin] == -1) now = TRIE::nodes[now].nxt[FAIL];
		now = TRIE::nodes[now].nxt[c - margin];
		count += correct[now];
		return (count);
	}
};

int needs[111111];
string in[111111];
//https://codeforces.com/problemset/problem/963/D
int main(){
	
	fastcin();
	AhoCorasick<26, 'a'> aho;
	
	string str;cin >> str;
	int n;cin >> n;
	REP(i,n){
		cin >> needs[i];
		cin >> in[i];
		aho.add(in[i]);
	}
	aho.build();
	vector<vector<int>> ans(n);
	aho.match(str, ans);
	
	REP(i,n){
		if(ans[i].size() < needs[i]){
			cout << -1 << endl;
			continue;
		}
		
		int out = INF;
		REP(j,ans[i].size() - needs[i] + 1){
			out = min(out, ans[i][j+needs[i]-1] - ans[i][j] + (int)in[i].size());
		}
		cout << out << endl;
	}
	
	return 0;
}
