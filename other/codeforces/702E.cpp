#include<bits/stdc++.h>
using namespace std;
#define int long long

struct Node {
   vector<int> stidx = vector<int>(35), stmin = vector<int>(35), stsum = vector<int>(35);
};

signed main() {
   int N,K;
   cin>>N>>K;

   vector<Node> nodes(N);
   for(int n=0;n<N;++n) { cin>>nodes[n].stidx[0]; }
   for(int n=0;n<N;++n) { cin>>nodes[n].stmin[0]; nodes[n].stsum[0]=nodes[n].stmin[0]; }

   for(int i=1;i<35;++i){
      for(int n=0;n<N;n++){
         int idxnext=nodes[n].stidx[i-1];
         nodes[n].stidx[i]=nodes[idxnext].stidx[i-1];
         nodes[n].stmin[i]=min(nodes[n].stmin[i-1], nodes[idxnext].stmin[i-1]);
         nodes[n].stsum[i]=nodes[n].stsum[i-1] + nodes[idxnext].stsum[i-1];
      }
   }

   for(int n=0;n<N;++n){
      int curr=n;
      int m=numeric_limits<int>::max(), s=0;
      for(int i=34;i>=0;--i){
         if(K & (1LL<<i)) {
            m=min(m, nodes[curr].stmin[i]);
            s=s+nodes[curr].stsum[i];
            curr=nodes[curr].stidx[i];
         }
      }

      cout<<s<<" "<<m<<"\n";
   }
}
