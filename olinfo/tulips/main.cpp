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

    vector<int> mem(N);
    mem[N-1] = T[N-1];
    for(int n=N-2; n>=0; --n) {
        mem[n] = min(T[n], mem[n+1]);
    }
    deb(mem);

    for(int k=1; k<K; ++k) {
        for(int n=0; n<N-k; ++n) {
            int minT = numeric_limits<int>::max();
            int maxSum = -1;
            for(int i=n; i<N-k; ++i) {
                minT = min(minT, T[i]);
                int sum = minT + mem[i+1];
                if (sum > maxSum) {
                    maxSum = sum;
                }
            }
            mem[n] = maxSum;
        }
        deb(mem);
    }

    out << mem[0] << endl;
}
