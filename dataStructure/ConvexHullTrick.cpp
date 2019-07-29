#include <bits/stdc++.h>

using namespace std;

#define REP(i,n) for(ll (i) = (0);(i) < (n);++i)

typedef long long ll;
typedef pair<ll,ll> P;

/*
評価する直線の傾きが単調減少
求めるxが単調増加の時の最小値
*/
class ConvexHullTrick_Monotony{
	const ll inf = 1e9; 
	struct Line{
		ll a,b;
		Line(ll x,ll y):a(x),b(y){};
	};

	deque<Line> deq;
	
public:	
	ConvexHullTrick_Monotony(){}
	void Add_back(ll a,ll b){
		if(deq.size() <= 1){
			deq.push_back(Line(a,b));
		}
		else{
			while(deq.size() > 1){
				ll a1 = deq[deq.size()-2].a;
				ll b1 = deq[deq.size()-2].b;
				ll a2 = deq[deq.size()-1].a;
				ll b2 = deq[deq.size()-1].b;
				if((b2 - b1)*(a2 - a) < (b - b2)*(a1 - a2)){
					break;
				}
				else{
					deq.pop_back();
				}
			}
			deq.push_back(Line(a,b));
		}
	}
	
	ll seek_front(ll x){
		while(deq.size() > 1 && deq[0].a * x + deq[0].b > deq[1].a * x + deq[1].b){
			deq.pop_front();
		}
		return deq[0].a * x + deq[0].b;
	}
};

int main(){
	ConvexHullTrick_Monotony CHT;
	
	int n;cin >> n;
	
	REP(i,n){
		ll a;cin >> a;
		CHT.Add_back(-2*(i+1),a+(i+1)*(i+1));
	}
	
	REP(i,n){
		cout << CHT.seek_front(i+1) + (i+1)*(i+1) << endl;
	}
	
	return 0;
}
