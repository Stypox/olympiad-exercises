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

struct Terminal {
    int par=-1;
    int rank=1;
    int zRelat=-1; // will be -1 for roots
};

vector<Terminal> terminals;

// 'root' and 'merge' functions implement the Union Find Disjoint Set algorithm

// returns the following pair:
// - index of the root terminal of the connected set to which 'a' belongs
// - potential difference from 'a' to the root terminal
pair<int, int> root(int a) {
    if (terminals[a].par == -1) return {a, 0};
    int par, zRelat;
    tie(par, zRelat) = root(terminals[a].par);
    return make_pair(par, zRelat + terminals[a].zRelat);
}

// Tries to connect the two terminals 'a' and 'b' with a component
// with a potential difference of 'z'. Returns whether the new
// component was added successfully. Placing the component fails
// if the two terminals were already connected some other way and
// their potential difference is different than 'z'.
bool merge(int a, int b, int z) {
    // calculate the root terminals of 'a' and 'b'
    int ra, za, rb, zb;
    tie(ra, za) = root(a);
    tie(rb, zb) = root(b);

    if (ra == rb) {
        // if the roots are the same, then the two terminals are
        // already connected in some way, so return whether the
        // potential difference between them is correct
        return za - zb == z;
    }

    // use the rank to make sure the sets (which are actually trees)
    // do not grow too high, to ensure an O(log n) complexity (we
    // could do even better with path compression but who cares)
    if (terminals[ra].rank > terminals[rb].rank) {
        swap(ra,rb);
        swap(za,zb);
        swap(a,b);
        z=-z;
    }

    // now rb has surely the highest rank, connect ra to rb
    terminals[ra].par = rb; // the parent of 'ra', and the root of its subtree, is now 'rb'
    terminals[ra].zRelat = z-za+zb; // the potential difference between the roots
    terminals[rb].rank = max(terminals[rb].rank, terminals[ra].rank + 1); // update rank
    return true; // component added successfully
}

signed main() {
	int N,M;
    in>>N>>M;
    terminals.resize(N);

    for(int m=0;m<M;++m){
        int a,b,z;
        in>>a>>b>>z;

        if (!merge(a,b,z)) {
            out<<m<<"\n";
            return 0;
        }
    }

    out<<M<<"\n";
    return 0;
}
