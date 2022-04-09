int gcd(int a, int b) {
	int r=a%b;
	if(r==0) return b;
	return gcd(b,r);
}

// USARE FILE rabin_karp_hash_multiplicative_inverse.cpp
// E' MOLTO PIU FACILE FARE k^(m-2) IN FAST EXP
int multiplicativeInverse(int k, int m) {
	vector<int> y{0,0,0,1}, q{0,0}, r{m, k};

	int i=2;
	while(1){
		if (i>=4) y.push_back(y[i-2] - y[i-1] * q[i-2]);
		q.push_back(r[i-2] / r[i-1]);
		r.push_back(r[i-2] % r[i-1]);

		if (r.back() == 0) {
			break;
		}
		++i;
	}

	int res = (y[y.size()-2] - y[y.size()-1] * q[q.size()-2] + m) % m;
	assert(((res*k) % m) == 1);
	return res;
}

int partialBinom(int n, int k) {
	int res=1;
	for(int i=k+1;i<=n;++i) {
		res*=i;
		res%=M;
	}
	return res;
}

int32_t main() {
	int N;
	in>>N;
   if(N<=6){
		int k[]={10,2,7,13,41,31};
		out<<k[N-1]<<"\n";
		return 0;
	}

	int res=1; // parti con 000000
	int freq[10]={0,0,0,0,0,0,0,0,0,0};
	int numOnes, currPartialBinom;

	int memMultInv[21];
	for (int i=2;i<21;++i){
		memMultInv[i]=multiplicativeInverse(i,M);
	}

	function<void(int, int, int)> rec = [&](int m, int c, int mul) {
		if (mul > (N + 200)) {
			return;
		}
		mul %= M;

		if (c==0) {
			int sum=numOnes;
			for(int i=2;i<10;++i){
				sum += i*freq[i];
			}
			sum%=M;

			if (mul==sum) {
				int binom = currPartialBinom;
				for(int i=0;i<10;++i){
					for(int j=2;j<=freq[i];++j){
						binom *= memMultInv[j];
						binom %= M;
					}
				}
				res+=binom;
				res%=M;
			}

			return;
		}

		for (int i=m;i<10;++i) {
			freq[i]++;
			rec(i, c-1, mul*i);
			freq[i]--;
		}
	};

	for (numOnes=N-min(N, (int)20);numOnes<N;++numOnes){
		currPartialBinom=partialBinom(N,numOnes);
		rec(2, N-numOnes, 1);
	}

	out<<(res + M) % M<<"\n";
}