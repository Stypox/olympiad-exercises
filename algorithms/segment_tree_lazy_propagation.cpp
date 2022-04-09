#pragma GCC optimize ("Ofast")
#include <vector>
#include <limits>
#include <optional>
#ifndef EVAL
#include <string>
#include <iostream>
#include <iomanip>
#endif
using namespace std;

#define inline __attribute__((always_inline)) inline
using ll=long long;

enum class Mode : char { none, add, set };

struct Node {
   ll min = numeric_limits<ll>::max();
   ll sum = 0;

   ll update = 0;
   Mode mode = Mode::none;
};

int greaterPow2(int i) {
   int j=1;
   while (j<i) {
      j*=2;
   }
   return j;
}

struct SegmentTree {
   vector<Node> dat;

   SegmentTree() {}

   SegmentTree(const vector<ll>& v) : dat{(size_t) 2*greaterPow2(v.size())} {
      setup(v, a0(), b0(), i0());
   }

   void setup(const vector<ll>& v, int a, int b, int i) {
      if (b-a == 1) {
         if (a < (ll)v.size()) {
            dat[i].min = v[a];
            dat[i].sum = v[a];
         }
         return;
      }
      setup(v, a, (a+b)/2, i*2);
      setup(v, (a+b)/2, b, i*2+1);
      setup(i);
   }

   void setup(int i) {
      if (i*2 >= (ll)dat.size()) return;
      dat[i].min = min(dat[i*2].min, dat[i*2+1].min);
      dat[i].sum = dat[i*2].sum + dat[i*2+1].sum;
   }

   void lazyPropStep(int a, int b, int i, ll update, Mode mode) {
      if(mode == Mode::none) {
         return;
      } else if (mode == Mode::add) {
         if (dat[i].mode == Mode::none) {
            dat[i].update = 0; // just in case
         }

         dat[i].min += update;
         dat[i].sum += (b-a)*update;
         dat[i].update += update;

         if (dat[i].mode == Mode::none) {
            dat[i].mode = Mode::add; // do not change Mode::set
         }

      } else /* mode == Mode::set */ {
         dat[i].min = update;
         dat[i].sum = (b-a)*update;
         dat[i].update = update;
         dat[i].mode = Mode::set;
      }
   }

   void lazyProp(int a, int b, int i) {
      if (i*2 >= (ll)dat.size()) return;
      lazyPropStep(a, (a+b)/2, i*2,   dat[i].update, dat[i].mode);
      lazyPropStep((a+b)/2, b, i*2+1, dat[i].update, dat[i].mode);
      dat[i].update = 0;
      dat[i].mode = Mode::none;
   }


   ll queryMin(int l, int r, int a, int b, int i) {
      if (a>=r || b<=l) return numeric_limits<int>::max();
      if (a>=l && b<=r) return dat[i].min;
      lazyProp(a, b, i);
      return min(queryMin(l, r, a, (a+b)/2, i*2),
                 queryMin(l, r, (a+b)/2, b, i*2+1));
   }

   ll querySum(int l, int r, int a, int b, int i) {
      if (a>=r || b<=l) return 0;
      if (a>=l && b<=r) return dat[i].sum;
      lazyProp(a, b, i);
      return querySum(l, r, a, (a+b)/2, i*2)
           + querySum(l, r, (a+b)/2, b, i*2+1);
   }

   void lazyAdd(int l, int r, ll x, int a, int b, int i) {
      if (a>=r || b<=l) return;
      lazyProp(a, b, i);

      if (a>=l && b<=r) {
         dat[i].min += x;
         dat[i].sum += (b-a)*x;
         dat[i].update = x;
         dat[i].mode = Mode::add;
         return;
      }

      lazyAdd(l, r, x, a, (a+b)/2, i*2);
      lazyAdd(l, r, x, (a+b)/2, b, i*2+1);
      setup(i);
   }

   void lazySet(int l, int r, ll x, int a, int b, int i) {
      if (a>=r || b<=l) return;
      lazyProp(a, b, i);

      if (a>=l && b<=r) {
         dat[i].min = x;
         dat[i].sum = (b-a)*x;
         dat[i].update = x;
         dat[i].mode = Mode::set;
         return;
      }

      lazySet(l, r, x, a, (a+b)/2, i*2);
      lazySet(l, r, x, (a+b)/2, b, i*2+1);
      setup(i);
   }

   int lowerBound(int l, int r, ll x, int a, int b, int i) {
      if (a>=r || b<=l || dat[i].min > x) return -1;
      if (b-a == 1) return a;
      lazyProp(a, b, i);

      int left = lowerBound(l, r, x, a, (a+b)/2, i*2);
      if (left != -1) return left;
      return lowerBound(l, r, x, (a+b)/2, b, i*2+1);
   }

   inline int a0() { return 0; }
   inline int b0() { return dat.size()/2; }
   inline int i0() { return 1; }
   void print() {
      #ifndef EVAL
      cout<<"\n";
      int dist=dat.size()*9;
      for(int i=1;i<(ll)dat.size();++i) {
         if ((i ^ (i-1)) == (2*i-1)) {
            cout<<"\n";
            dist /= 2;
         }
         string s = i*2>=(ll)dat.size() ? to_string(dat[i].sum) : ((dat[i].min==numeric_limits<ll>::max() ? string{"inf"} : to_string(dat[i].min)) + "," + to_string(dat[i].sum));
         s += (dat[i].mode == Mode::none ? "n" : dat[i].mode == Mode::add ? "a" : "s") + to_string(dat[i].update);
         int realdist = dist - s.length();
         cout<<setw(realdist/2 + realdist%2)<<""<<s<<setw(realdist/2)<<"";
      }
      cout<<"\n";
      for(int n=0;n<(ll)dat.size()/2;++n){
         string s = to_string(n);
         int realdist = dist - s.length();
         cout<<setw(realdist/2 + realdist%2)<<""<<s<<setw(realdist/2)<<"";
      }
      cout<<"\n";
      cout<<"\n";
      #endif
   }
};

SegmentTree st;

void init(vector<ll> a) {
   st = SegmentTree(a);
}

ll get_min(int l, int r) {
   return st.queryMin(l, r, st.a0(), st.b0(), st.i0());
}

ll get_sum(int l, int r) {
   return st.querySum(l, r, st.a0(), st.b0(), st.i0());
}

void add(int l, int r, ll x) {
   st.lazyAdd(l, r, x, st.a0(), st.b0(), st.i0());
}

void set_range(int l, int r, ll x) {
   st.lazySet(l, r, x, st.a0(), st.b0(), st.i0());
}

int lower_bound(int l, int r, ll x) {
   return st.lowerBound(l, r, x, st.a0(), st.b0(), st.i0());
}