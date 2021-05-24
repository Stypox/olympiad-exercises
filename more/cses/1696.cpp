#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

istream& in = cin;
ostream& out = cout;
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

signed main() {
   int N,M,K;
   in>>N>>M>>K;
   int tot = N+M+2, S=0, T=tot-1;

   vector<vector<int>> adj(tot), capacity(tot, vector<int>(tot, 0));
   for(int k=0;k<K;++k){
      int A,B;
      in>>A>>B;
      B+=N;
      if (capacity[A][B] == 0) {
         adj[A].push_back(B);
         adj[B].push_back(A);
         capacity[A][B] = 1;
      }
   }

   for(int n=1;n<=N;++n) {
      adj[0].push_back(n);
      adj[n].push_back(0);
      capacity[0][n] = 1;
   }
   for(int m=1;m<=M;++m) {
      adj[N+m].push_back(tot-1);
      adj[tot-1].push_back(N+m);
      capacity[N+m][tot-1] = 1;
   }

   vector<int> parent(tot);
   auto bfsAugmentingPath = [&]() -> int {
      fill(parent.begin(), parent.end(), -1);
      parent[S]=-2;
      queue<pair<int, int>> q;
      q.push({S, numeric_limits<int>::max()});

      while(!q.empty()) {
         auto [i, flow] = q.front();
         q.pop();

         for(int e : adj[i]) {
            if (parent[e] == -1 && capacity[i][e] > 0) {
               parent[e] = i;
               int partialFlow = min(capacity[i][e], flow);
               if (e == T) return partialFlow;
               q.push({e, partialFlow});
            }
         }
      }
      return 0;
   };

   int flow=0;
   while (1) {
      int partialFlow = bfsAugmentingPath();
      if (partialFlow == 0) break;
      flow += partialFlow;

      int curr=T;
      while(curr!=S) {
         int par = parent[curr];
         capacity[par][curr] -= 1;
         capacity[curr][par] += 1;
         curr=par;
      }
   }

   out<<flow<<"\n";
   for(int n=1;n<=N;++n) {
      for(int m : adj[n]) {
         if(capacity[n][m] == 0 && m != 0) {
            out<<n<<" "<<m-N<<"\n";
         }
      }
   }
}





