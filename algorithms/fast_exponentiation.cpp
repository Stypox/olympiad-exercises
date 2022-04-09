#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define MOD 32749

ifstream in{"input.txt"};
ofstream out{"output.txt"};

struct Mat{
   int e00, e01,
       e10, e11; // riga-colonna
};

Mat multiply(const Mat& a, const Mat& b) {
   return {(a.e00*b.e00 + a.e01*b.e10) % MOD, (a.e00*b.e01 + a.e01*b.e11) % MOD,
           (a.e10*b.e00 + a.e11*b.e10) % MOD, (a.e10*b.e01 + a.e11*b.e11) % MOD};
}

Mat fastExp(const Mat& m, int exp){
   if (exp == 0) return {1, 0,
                         0, 1};

   Mat k = fastExp(m, exp/2);
   Mat res = multiply(k, k);
   if (exp % 2 == 1) return multiply(res, m);
   return res;
}

int32_t main() {
   int N;
   in>>N;

   Mat mat{3, 2,
           3, 3};
   mat = fastExp(mat, N);
   mat = multiply(mat, {1, 0, 0, 0});
   out<<mat.e00<<" "<<mat.e10<<"\n";
}