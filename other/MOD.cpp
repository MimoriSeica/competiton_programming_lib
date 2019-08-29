#define MOD 1000000007

long long totient(long long a) {
	ll ret = a;
	for(int i = 2;i * i <= a;i++){
		if(a % i == 0){
			ret = ret * (i - 1) / i;
			while(a % i == 0)a /= i;
		}
	}
	if(a > 1)ret = ret * (a - 1) / a;
	return ret;
}

// a / b (mod p) b と p は互いに素
// O(sqrt(p))かかるので注意
long long totient_div(long long a, long long b, long long p) {
	long long ret = a;
	long long tp = totient(p) - 1;
	long long c = b;
	for(int i = 0;i <= 60;i++){
		if(tp & (1LL << i))ret = (ret * c) % p;
		c = (c * c) % p;
	}
	return ret;
}

//a^b % MOD
long long mod_pow(ll a,ll b){
	long long ret = 1;
	long long c = a;
	for(int i = 0;i <= 60;i++){
		if(b & (1LL << i))ret = (ret * c) % MOD;
		c = (c * c) % MOD;
	}
	return ret;
}

//ａをbで割る
long long mod_div(long long a,long long b){
	long long tmp = MOD - 2,c = b,ret = 1;
	while(tmp > 0){
		if(tmp & 1){
			ret *= c;ret %= MOD;
		}
		c *= c;c %= MOD;tmp >>= 1;
	}
	return a*ret%MOD;
}

#define MAX_K 333333
vector<long long> fact(MAX_K);
long long combination(long long n, long long r){
    if(n < r || n < 0 || r < 0)
        return 0;
	if(fact[0] != 1){
		fact[0] = 1;
		for(long long i = 1;i < MAX_K;i++)fact[i] = (fact[i-1] * i) % MOD;
	}
    long long ret = fact[n];
	long long tmp = (fact[r] * fact[n-r]) % MOD;
    return mod_div(ret,tmp);
}
