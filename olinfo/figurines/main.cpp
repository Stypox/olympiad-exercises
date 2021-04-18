#include <bits/stdc++.h>
using namespace std;

int lsOne(int i){
   return i & -i;
}

vector<vector<int>> a;
vector<vector<int>> r;

void init(int n) {
   a.resize(n+1);
   r.resize(n+1);
}

int dLog = 1;
void log(vector<int>& a1, vector<int>& r1) {
   int d = dLog;
   while(d < (int)a.size()) {
      a[d].insert(a[d].end(), a1.begin(), a1.end());
      r[d].insert(r[d].end(), r1.begin(), r1.end());
      d += lsOne(d);
   }

   if (dLog == ((int)a.size()-1)) {
      for(auto& e : a) sort(e.begin(), e.end());
      for(auto& e : r) sort(e.begin(), e.end());
   }
   dLog++;
}

int answer(int d, int x) {
   int res=0;
   while (d > 0) {
      res += a[d].end() - lower_bound(a[d].begin(), a[d].end(), x);
      res -= r[d].end() - lower_bound(r[d].begin(), r[d].end(), x);
      d -= lsOne(d);
   }
   return res;
}
