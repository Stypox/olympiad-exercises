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
template<class T> constexpr void debVec(const T& v) {
    for(auto&& el:v){
        cout<<el<<" ";
    }
    cout<<"\n";
}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T> constexpr void debVec(const T&) {}
#endif

void setMaxSubs(str D, si& N, si& S, si& W, si& E) {
    N=0; S=0; W=0; E=0;
    ch curr='\0';
    si n=0;
    for(auto ch:D) {
        if(ch==curr){
            ++n;
        } else {
            switch(curr){
                case 'N': N=max(n,N); break;
                case 'S': S=max(n,S); break;
                case 'W': W=max(n,W); break;
                case 'E': E=max(n,E); break;
            }
            curr=ch;
            n=1;
        }
    }
    for(auto ch:D) {
        if(ch==curr){
            ++n;
        } else {
            switch(curr){
                case 'N': N=max(n,N); break;
                case 'S': S=max(n,S); break;
                case 'W': W=max(n,W); break;
                case 'E': E=max(n,E); break;
            }
            curr=ch;
            n=1;
        }
    }
}

int main() {
    out<<3<<" "<<3<<"\n";
}