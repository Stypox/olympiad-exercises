#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

struct SegmentTree {
   vector<int> datmin, imax;
   int L;
   SegmentTree(int n) {
      int L=1;
      while (L<n) L*=2;
      datmin.resize(L*2, numeric_limits<int>::max());
      imax.resize(L*2, );
   }

   void set(int x, int v, int a, int b, int i) {
      if (x >= b || x < a) return;
      if (b-a == 1) {
         datmin[i] = v;
         return;
      }
      set(x, v, a, (a+b)/2, i*2);
      set(x, v, (a+b)/2, b, i*2+1);
      datmin[i] = min(datmin[i*2], datmin[i*2+1]);
      imax[i] = datmin[imax[i*2] + L] > datmin[imax[i*2+1] + L] ? imax[i*2] : imax[i*2+1];
   }

   int queryimax(int x, int y, int a, int b, int i) {
      if (x >= b || y <= a) return -1;
      if (a >= x && b <= y) return imax[i];

      int left = queryimax(x, y, a, (a+b)/2, i*2);
      int right = queryimax(x, y, (a+b)/2, b, i*2+1);
      return datmin[left + L] > datmin[right + L] ? left : right;
   }

   int firstSmaller(int x, int y, int v, int a, int b, int i) {
      if (x >= b || y <= a || datmin[i] >= v) return -1;
      if (b-a == 1) return i-datmin.size()/2;
      int left = firstSmaller(x, y, v, a, (a+b)/2, i*2);
      if (left != -1) return left;
      else return firstSmaller(x, y, v, (a+b)/2, b, i*2+1);
   }
};

signed main() {
   int N;
   in>>N;
   
   SegmentTree st(N);
   vector<int> S(N);
   for(int n=0;n<N;++n){
      in>>S[n];
      st.set(n, S[n], 0, st.datmin.size()/2, 1);
   }

   int bestlength=0;
   for(int n=0;n<N;++n){
      int iFirstSmaller = st.firstSmaller(n, N, S[n], 0, st.L, 1);
      if (iFirstSmaller == -1) iFirstSmaller=N;
      int iMax = st.queryimax(n, iFirstSmaller, 0, st.L, 1);
      deb(iFirstSmaller, iMax);
      bestlength = max(bestlength, iMax - n);
   }

   out<<bestlength<<"\n";
}

