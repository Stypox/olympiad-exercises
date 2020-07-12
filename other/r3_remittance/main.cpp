#pragma GCC optimize ("O3")
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

int main() {
	si N;
    in>>N;

    vec<si>real(N),wanted(N);
    for(si n=0;n!=N;++n){
        in>>real[n]>>wanted[n];
    }

    si i=0,editedLastTime=true,editedLastLastTime=true;
    while(1){
        si addToNext=0;
        if(real[i]>wanted[i]) addToNext=(real[i]-wanted[i]+1)/2;
        if(real[i]<2*addToNext) addToNext-=1;
        real[i]-=2*addToNext;

        ++i;
        if(i==N) {
            i=0;

            if(editedLastTime){
                editedLastTime=false;
                editedLastLastTime=true;
            }else{
                if(!editedLastLastTime) break;
                editedLastLastTime=false;
            }
        }
        real[i]+=addToNext;

        if(addToNext!=0) editedLastTime=true;
    }

    if (real==wanted) out<<"Yes";
    else out<<"No";
}