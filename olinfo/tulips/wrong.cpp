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
	int N, K;
    in >> N >> K;

    vector<int> T(N);
    for(int n=0; n<N; ++n) {
        in >> T[n];
    }

    vector<pair<int,int>> mem(N);
    mem[N-1] = { T[N-1], T[N-1] };
    for(int n=N-2; n>=0; --n) {
        int val = min(T[n], mem[n+1].first);
        mem[n] = { val, val };
    }

    pair<int,int> prevNp1;
    for(int k=1; k<K; ++k) {
        prevNp1 = mem[N-k-1];
        mem[N-k-1] = { mem[N-k].first + T[N-k-1], T[N-k-1] };
        for(int n=N-k-2; n>=0; --n) {
            pair<int,int> nextPrev = mem[n];
            int extendSum = mem[n+1].first + min(T[n] - mem[n+1].second, (int)0);
            int newGroupSum = prevNp1.first + T[n];

            if (extendSum > newGroupSum) {
                mem[n] = { extendSum, min(T[n], mem[n+1].second) };
            } else {
                mem[n] = { newGroupSum, T[n] };
            }

            prevNp1 = nextPrev;
        }
        deb(mem);
    }

    deb(mem[0]);
    out << mem[0].first << endl;
}
