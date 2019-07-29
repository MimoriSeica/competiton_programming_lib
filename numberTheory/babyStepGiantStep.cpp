//g^x = y(mod MOD)を満たすxを探す
long long babyStepGiantStep(ll g, ll y) {
	long long m = sqrt(MOD) + 1;
	map<long long,long long> mp;
	long long tmp = 1;
	for(int i = 0;i < m;i++){
		mp[tmp] = i;
		tmp = (tmp * g) % MOD;
	}
	long long gm = 1;
	for(int i = 0;i < m;i++)gm = (gm * g) % MOD;
	long long factg = mod_div(1, gm);
	long long ganma = y;
	for(int i = 0;i < m;i++){
		auto it = mp.find(ganma);
		if(it != mp.end()){
			return i * m + (it->second);
		}
		ganma = ganma * factg % MOD;
	}
	return -1;
}
