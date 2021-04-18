#include <bits/stdc++.h>
using namespace std;

struct Node {
   int a;
   int sum=0;
   vector<int> cons;
   vector<int> propagateTo;
   vector<int> readFrom;
};

vector<Node> nodes;

void init(vector<int> a, vector<pair<int, int>> edges) {
   nodes.resize(a.size());
   for(int n=0;n<(int)a.size();++n) {
      nodes[n].a=a[n];
   }

   for (auto [from, to] : edges){
      nodes[from].cons.push_back(to);
   }

   int k=sqrt(a.size());
   for (int n=0;n<(int)a.size();++n) {
      if ((int)nodes[n].cons.size() >= k) {
         // prevent propagateTo
         for(auto con:nodes[n].cons){
            nodes[con].readFrom.push_back(n);
         }
      } else {
         // enforce propagateTo
         for(auto con:nodes[n].cons){
            nodes[n].propagateTo.push_back(con);
            nodes[con].sum += nodes[n].a;
         }
      }
   }
}

void modify(int i, int v) {
   for(auto con:nodes[i].propagateTo) {
      nodes[con].sum += (v - nodes[i].a);
   }
}

int get_sum(int i) {
   int res = nodes[i].sum;
   for(auto con:nodes[i].readFrom) {
      res += nodes[con].a;
   }
	return res;
}
