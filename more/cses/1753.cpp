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
   string a,b;
   in>>a>>b;

   string s=b+" "+a;
   vector<int> z(s.size());
   int l=0,r=1,i=0;

   const auto advancer = [&](){
      l=i;
      while(r < s.size() && s[r-i] == s[r]) ++r;
      z[i]=r-l;
   };

   while(++i<s.length()) {
      if (i>=r){
         r=i;
         advancer();
      } else {
         int k=i-l;
         if (z[k] < r-i) {
            z[i]=z[k];
         } else {
            advancer();
         }
      }
      deb(i,"(",r,",",l,")",z[i]);
   }

   deb(z);
   out<<count(z.begin()+b.size(), z.end(), b.size())<<"\n";
}
