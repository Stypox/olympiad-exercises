#include<bits/stdc++.h>
using namespace std;
#define int long long

struct Node{
   int v=0;
   int parent=-1;
   vector<int> children;
};

void nak(){
   cout<<"NIE\n";
   exit(0);
}

signed main(){
   int N;
   cin>>N;

   vector<Node> nodes(N);
   for (int i=-1;i<3;i+=2) for (int n=0;n<N;++n){
      int x;
      cin>>x;
      nodes[n].v -= i*x;
   }

   for (int n=0;n<N-1;++n){
      int a,b;
      cin>>a>>b;
      a--;b--;

      if (a>b) swap(a,b);
      nodes[a].children.push_back(b);
      nodes[b].parent = a;
   }

   int totmov=0;
   function<pair<int,int>(int)> dfs = [&](int x) -> pair<int,int> {
      vector<int> nodiSingoli;
      int valNodiGenit=numeric_limits<int>::max();
      for(int e:nodes[x].children){
         if(nodes[e].children.empty()){
            nodiSingoli.push_back(e);
         } else {
            auto [v,diff]=dfs(e);
            nodes[x].v-=diff;
            if (valNodiGenit == numeric_limits<int>::max()){
               valNodiGenit = v;
            } else if (valNodiGenit != v) {
               nak();
            }
         }
      }

      if(valNodiGenit==numeric_limits<int>::max()) valNodiGenit=0;

      for(int e:nodiSingoli){
         int diff=valNodiGenit-nodes[e].v;
         if (diff>0) nak();
         totmov-=diff;
      }

      if(valNodiGenit>0) nak();
      totmov-=valNodiGenit;
      return pair{nodes[x].v+valNodiGenit, valNodiGenit};
   };

   auto [v, diff] = dfs(0);
   if (v!=0) nak();
   cout<<"TAK\n"<<totmov<<"\n";
}
