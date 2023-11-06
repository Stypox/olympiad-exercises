#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

signed main() {
	int N,K;
    in>>N>>K;
    K--;

    vector<int> V(N);
    for(int n=0;n<N;++n){
        in>>V[n];
        V[n]--;
    }

    int cnt=0;
    vector<bool> vis(N, false);

    int cur=0;
    while(cur != K && vis[cur] == false) {
        vis[cur] = true;
        cur = V[cur];
        ++cnt;
    }

    if (cur != K) {
        cnt=-1;
    }
    out<<cnt<<endl;
}
