#include<bits/stdc++.h>
using namespace std;
#define int long long

struct Node{
   int cost;
   vector<int> to,from;
   int tout=-1;
   bool condensed=false;
};

struct NodeCond{
   vector<int> costs;
};

signed main() {
   int N;
   cin>>N;

   vector<Node> nodes(N);
   for (int n=0;n<N;++n){
      cin>>nodes[n].cost;
   }

   int M;
   cin>>M;
   for(int m=0;m<M;++m){
      int a,b;
      cin>>a>>b;
      a--;
      b--;
      nodes[a].to.push_back(b);
      nodes[b].from.push_back(a);
   }

   vector<int> ordered;
   function<void(int)> dfs = [&](int i){
      if (nodes[i].tout!=-1) return;
      nodes[i].tout=0;
      for(auto e:nodes[i].to){
         dfs(e);
      }
      ordered.push_back(i);
      //cout<<i<<"\n";
   };
   for(int n=0;n<N;++n){
      dfs(n);
   }

   int currNode=0;
   vector<NodeCond> nodeConds;
   function<void(int)> dfsReverse = [&](int i){
      if (nodes[i].condensed) return;
      nodes[i].condensed = true;
      nodeConds[currNode].costs.push_back(nodes[i].cost);
      for(auto e:nodes[i].from){
         dfsReverse(e);
      }
   };

   assert(ordered.size() == N);
   for(int n=N-1;n>=0;--n){
      if (nodes[ordered[n]].condensed) continue;
      nodeConds.emplace_back();
      dfsReverse(ordered[n]);
      currNode++;
   }

   int res=1;
   int money=0;
   for(int k=0;k<currNode;++k){
      sort(nodeConds[k].costs.begin(), nodeConds[k].costs.end());
      money+=nodeConds[k].costs[0];
      auto fine = upper_bound(nodeConds[k].costs.begin(), nodeConds[k].costs.end(), nodeConds[k].costs[0]);
      res*=(fine-nodeConds[k].costs.begin());
      res %= 1000000007;
   }

   cout<<money<<" "<<res<<"\n";
}
