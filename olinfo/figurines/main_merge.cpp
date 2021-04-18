#include <bits/stdc++.h>
using namespace std;

vector<int> merge(const vector<int>& a, const vector<int>& b) {
   vector<int> result;
   int i=0,j=0;
   while(1){
      if(i>=(int)a.size()) {
         if(j>=(int)b.size()) {
            break;
         }
         result.push_back(b.at(j));
         ++j;
      } else if (j>=(int)b.size()) {
         result.push_back(a.at(i));
         ++i;
      } else {
         if (a.at(i) < b.at(j)) {
            result.push_back(a.at(i));
            ++i;
         } else {
            result.push_back(b.at(j));
            ++j;
         }
      }
   }
   return result;
}

struct Node {
   vector<int> added, removed;
   void combine(vector<int>& a1, vector<int>& r1) {
      added.insert(added.end(), a1.begin(), a1.end());
      removed.insert(removed.end(), r1.begin(), r1.end());
   }
   void combine1(vector<int>& a1, vector<int>& r1) {
      vector<int> allAdded = merge(added, a1);
      vector<int> allRemoved = merge(removed, r1);
      added.clear();
      removed.clear();

      int i=0,j=0;
      while(1){
         if(i>=(int)allAdded.size()) {
            if(j>=(int)allRemoved.size()) {
               break;
            }
            removed.push_back((int)allRemoved.at(j));
            ++j;
         } else if (j>=(int)allRemoved.size()) {
            added.push_back(allAdded.at(i));
            ++i;
         } else {
            if (allAdded.at(i) < allRemoved.at(j)) {
               added.push_back(allAdded.at(i));
               ++i;
            } else if (allAdded.at(i) > allRemoved.at(j)) {
               removed.push_back(allRemoved.at(j));
               ++j;
            } else {
               ++i;
               ++j;
            }
         }
      }
   }
};

int lsOne(int i){
   return i & -i;
}

struct FenwickTree {
   vector<Node> dat;
   FenwickTree(int n) : dat{(size_t) n+1} {}

   void put(int d, vector<int>& added, vector<int>& removed) {
      //sort(added.begin(), added.end());
      //sort(removed.begin(), removed.end());
      while(d < (int)dat.size()) {
         dat[d].combine(added, removed);
         d += lsOne(d);
      }
   }

   int answer(int d, int x) {
      int res=0;
      while (d > 0) {
         auto [added, removed] = dat[d];
         res += added.end() - lower_bound(added.begin(), added.end(), x);
         res -= removed.end() - lower_bound(removed.begin(), removed.end(), x);
         d -= lsOne(d);
      }
      return res;
   }
};

FenwickTree ft(0);

void init(int n) {
   ft=FenwickTree(n);
}

int dLog = 0;
void log(vector<int>& added, vector<int>& removed) {
   dLog++;
   ft.put(dLog, added, removed);
   if (dLog == ft.dat.size()-1) {
      for(auto&& n : ft.dat) {
         sort(n.added.begin(), n.added.end());
         sort(n.removed.begin(), n.removed.end());
      }
   }
}

int answer(int d, int x) {
	return ft.answer(d, x);
}
