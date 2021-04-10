#include <bits/stdc++.h>
using namespace std;
#define int long long

struct Frog {
   int from=-1,to,i;
   bool operator<(const Frog& other) const {
      return to == other.to ? (from > other.from) : (to < other.to);
   }
   bool operator<(const int& other) const {
      return to < other;
   }
};

struct Bug {
   int x,size;
   bool operator<(const Bug& other) const {
      return x < other.x;
   }
};

signed main(){
   int N,M;
   cin>>N>>M;

   set<Frog> frogs;
   vector<int> tongueLength(N);
   vector<int> bugsEaten(N);
   for(int n=0;n<N;++n){
      Frog frog;
      cin>>frog.from>>frog.to;
      tongueLength[n]=frog.to;

      frog.to += frog.from;
      frog.i=n;
      frogs.insert(frog);
   }

   vector<Bug> bugs(M);
   for(int m=0;m<M;++m){
      cin>>bugs[m].x>>bugs[m].size;
   }

   int minfromsofar = numeric_limits<int>::max();
   auto rbegin=frogs.end(); auto rend=frogs.begin(); --rbegin; --rend;
   for(auto it=rbegin;it!=rend;--it){
      cout<<minfromsofar<<" "<<it->from<<" "<<it->to<<"\n";

      if(it->from >= minfromsofar) {
         frogs.erase(it);
      } else {
         minfromsofar=it->from;
      }
   }

//   sort(bugs.begin(), bugs.end());
   for(auto [x, size] : bugs) {
      for(auto frog:frogs) cout<<x<<" "<<size<<" | "<<frog.i<<" | "<<frog.from<<" "<<frog.to<<" "<<tongueLength[frog.i]<<" "<<bugsEaten[frog.i]<<"\n"; cout<<"\n";

      Frog testFrog; testFrog.to=x; testFrog.from=x;
      auto it = frogs.lower_bound(testFrog);
      if (it == frogs.end()) continue;
      cout<<it->i<<" | "<<it->from<<" "<<it->to<<"\n\n";

      Frog newFrog = *it;
      newFrog.to += size;
      tongueLength[newFrog.i] += size;
      bugsEaten[newFrog.i]++;

      auto last=it;
      while(last!=frogs.end() && last->to <= newFrog.to) ++last;
      frogs.erase(it, last);

      frogs.insert(newFrog);
   }

   for(int n=0;n<N;++n){
      cout<<bugsEaten[n]<<" "<<tongueLength[n]<<"\n";
   }
}
