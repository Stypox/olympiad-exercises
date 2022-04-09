#define hash_t uint64_t
#define M 1000000007
#define P 59

struct Hash {
   size_t length;
   hash_t value;
};

array<int, 4002> Pexp;
array<int, 4002> PexpMulInv;

int fastExp(int x, int e){
   if (e==0) return 1;
   int half = fastExp(x, e/2);
   return ((half*half % M) * (e%2 == 1 ? x : 1)) % M;
}

hash_t getHash(const char* s, size_t l) {
   if (l==0) return 0;
   return (P*getHash(s+1, l-1) + s[0]) % M;
}

signed main() {
   int p=1;
   for(int i=0;i<(int)Pexp.size();++i){
      Pexp[i] = p;
      PexpMulInv[i] = fastExp(p, M-2);
      assert(PexpMulInv[i] * p % M == 1);
      p*=P;
      p%=M;
   }

	size_t N,K;
	in>>N>>K;

   string S;
   in>>S;
   for(char& c:S) c-='a'-1;

   vector<Hash> grammar;
   vector<string> Aorig;
   for(size_t k=0;k<K;++k){
      string A;
      in>>A;
      for(char& c:A) c-='a'-1;
      grammar.push_back({A.length(), getHash(A.c_str(), A.length())});
   }

   // calculate hashes for strings in S from 0 to any l
   vector<hash_t> hashes(N+1);
   int lasth=0;
   for(size_t l=0;l<N;++l){
      hashes[l]=lasth;
      lasth+=Pexp[l]*S[l];
      lasth%=M;
   }
   hashes[N]=lasth;

   vector<int> mem(N, -1);
   function<int(int)> dp = [&](size_t n) -> int {
      if (n>N) return 0;
      if (n==N) return 1;
      if (mem[n] != -1) return mem[n];

      int res=0;
      for(auto [l, h] : grammar) {
         if (n+l>N) {
            continue;
         }

         // obtain the hash of s in range [n, n+l) with prefix sum
         hash_t hcmp = (((hashes[n + l] - hashes[n] + M) % M) * PexpMulInv[n]) % M;
         if (hcmp == h) {
            res += dp(n+l);
            res %= M;
         }
      }

      mem[n] = res;
      return res;
   };

   out<<dp(0);
}