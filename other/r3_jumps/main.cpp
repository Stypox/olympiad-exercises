//#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template <typename T> using vec = vector<T>;

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
#endif

struct Val {
    si a,b,c;
};

int main() {
	si N,Q;
    in>>N;

    vec<si> A(N);
    for(si n=0; n<N; ++n) {
        in>>A[n];
    }
    auto sumA = [&A,&N](si a, si b, si c, si s, si e) {
        if(b-a>c-b || a<s || c>e) return (si)-1;
        return A[a]+A[b]+A[c];
    };

    vec<vec<Val>> v(N-2);
    si size=3;
    v[size-3].resize(N-size+1);
    for(si i=0;i!=N-size+1;++i) {
        v[size-3][i] = Val{i,i+1,i+2};
    }

    auto getPlus = [&sumA](const Val& val, si s, si e) {
        si maxsumsofar = -1;
        si ma,mb,mc;
        
        for(si ic=0;ic<=1;++ic){
            si cc = (ic?e:val.c);
            for(si ib=0;ib<=1;++ib){
                si cb = (ib?val.a+(cc-val.a)/2:val.b);
                for(si ia=0;ia<=1;++ia){
                    si ca = (ia?cb-(cc-cb):val.a);

                    si sum=sumA(ca,cb,cc,s,e);
                    if (sum>maxsumsofar){
                        maxsumsofar=sum;
                        ma=ca; mb=cb; mc=cc;
                    }
                }
            }
        }

        return tuple<si,si,si,si>{maxsumsofar,ma,mb,mc};
    };

    auto getMinus = [&sumA](const Val& val, si s, si e) {
        si maxsumsofar = -1;
        si ma,mb,mc;
        
        for(si ia=0;ia<=1;++ia){
            si ca = (ia?s:val.a);
            for(si ib=0;ib<=1;++ib){
                si cb = (ib?ca+(val.c-ca)/2:val.b);
                for(si ic=0;ic<=1;++ic){
                    si cc = (ic?ca+(cb-ca)*2:val.a);

                    si sum=sumA(ca,cb,cc,s,e);
                    if (sum>maxsumsofar){
                        maxsumsofar=sum;
                        ma=ca; mb=cb; mc=cc;
                    }
                }
            }
        }

        return tuple<si,si,si,si>{maxsumsofar,ma,mb,mc};
    };

    for(size=4;size<=N;++size) {
        v[size-3].resize(N-size+1);
        for(si i=0;i!=N-size+1;++i) {
            auto plus  =  getPlus(v[size-4][i],   i, i+size+1);
            auto minus = getMinus(v[size-4][i+1], i, i+size+1);
            if(get<0>(plus)>=get<0>(minus)) {
                v[size-3][i] = Val{get<1>(plus),get<2>(plus),get<3>(plus)};
            } else {
                v[size-3][i] = Val{get<1>(minus),get<2>(minus),get<3>(minus)};
            }
        }
    }

    in>>Q;
    for(si q=0; q<Q; ++q) {
        si s,e;
        in>>s>>e;
        --s;
        --e;

        si thisSize=e-s;
        out<<A[v[thisSize-3][s].a]+A[v[thisSize-3][s].b]+A[v[thisSize-3][s].c]<<"\n";
    }
}