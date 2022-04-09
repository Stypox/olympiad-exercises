#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

struct Node {
   bool vis=false;
   int condensed=-1;
   vector<int> to, from;
};

struct CNode {
   vector<int> nodes;
   vector<int> to, from;
};

int paper(int N, int M, int A[], int B[]) {
   vector<Node> nodes(N);
   for(int m=0;m<M;++m){
      A[m]--; B[m]--;
      nodes[A[m]].to.push_back(B[m]);
      nodes[B[m]].from.push_back(A[m]);
   }

   vector<int> ordinati;
   function<void(int)> toposort = [&](int i){
      if(nodes[i].vis) return;
      nodes[i].vis=true;
      for(auto e:nodes[i].to) toposort(e);
      ordinati.push_back(i);
   };
   for(int n=0;n<N;++n) toposort(n);
   //for(int n=0;n<N;++n) cout<<ordinati[n]+1<<" "; cout<<"\n";

   int c=0;
   vector<CNode> condensed;
   function<void(int)> condense = [&](int i){
      if(nodes[i].condensed!=-1) {
         if(nodes[i].condensed!=c) {
            condensed[c].from.push_back(nodes[i].condensed);
            condensed[nodes[i].condensed].to.push_back(c);
         }
         return;
      }
      nodes[i].condensed=c;
      condensed[c].nodes.push_back(i);
      for(auto e:nodes[i].from) condense(e);
   };

   for(int n=0;n<N;++n){
      if(nodes[ordinati[N-n-1]].condensed==-1) {
         condensed.emplace_back();
         condense(ordinati[N-n-1]);
         ++c;
      }
   }

   //for(auto&& k:condensed) cout<<k.nodes.size()<<";"<<k.from.size()<<";"<<k.to.size()<<" "; cout<<"\n";

   int x=-1;
   for(int i=0;i<c;++i){
      if(condensed[i].from.size()==0){
         if(x!=-1)return 0;
         x=i;
      }
   }

   if(x==-1) return 0;
   return condensed[x].nodes.size();
}