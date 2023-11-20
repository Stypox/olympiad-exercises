#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cerr<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cerr<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cerr<<", ";}cerr<<*it;}cerr<<"]";return o;}
void deb(){cerr<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cerr<<t;if(sizeof...(args)!=0){cerr<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

int lsOne(int i) {
    return i & -i;
}

signed main() {
    int N;
    cin >> N;
    cin.ignore();

    vector<vector<int>> added(N+1), removed(N+1);

    for (int n=0; n<N; ++n) {
        string s;
        getline(cin, s);
        if (s.empty()) {
            continue;
        }
        istringstream ss{s};

        while(!ss.eof()){
            char sign = ss.get();
            int figurine;
            ss >> figurine;
            ss.ignore();

            if (sign == '+') {
                int d = n+1;
                while (d <= N) {
                    added[d].push_back(figurine);
                    d += lsOne(d);
                }
            } else {
                assert(sign == '-');
                int d = n+1;
                while (d <= N) {
                    removed[d].push_back(figurine);
                    d += lsOne(d);
                }
            }
        }
    }

    for (int n=0; n<N; ++n) {
        sort(added[n].begin(), added[n].end());
        sort(removed[n].begin(), removed[n].end());
    }

    int x = 0;
    for (int n=0; n<N; ++n) {
        int d;
        cin >> d;

        int dx = 0;
        while (d > 0) {
            dx += added[d].end() - lower_bound(added[d].begin(), added[d].end(), x);
            dx -= removed[d].end() - lower_bound(removed[d].begin(), removed[d].end(), x);
            d -= lsOne(d);
        }
        x += dx;
        x %= N;
        deb(x, dx);
    }

    cout << x << endl;
}
