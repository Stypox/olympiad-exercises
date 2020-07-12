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
	si R,C;
    in>>R>>R>>C;
    str D;
    in>>D;

    vec<vec<si>> grids(R,vec<si>(C));
    for(si r=0;r!=R;++r){
        for(si c=0;c!=C;++c){
            in>>grids[r][c];
        }
    }
    
    si N,S,W,E;
    setMaxSubs(D,N,S,W,E);
    deb("N",N,"  S",S,"  W",W,"  E",E);

    vec<vec<si>> vals(R,vec<si>(C));
    for(si r=0;r!=R;++r){
        for(si c=0;c!=C;++c){            
            vec<vec<si>> grid{grids};
            if(grid[r][c]==0){
                vals[r][c]=numeric_limits<si>::max();
                continue;
            }

            queue<pair<si,si>> active;
            si numsick=1;
            grid[r][c]=-1;
            active.push({r,c});

            auto check = [&](si nr, si nc, si threshold){
                if(nr<0||nr>=R||nc<0||nc>=C) return;
                if(grid[nr][nc]<=0) return;
                if(grid[nr][nc]>threshold){
                    grid[nr][nc]-=threshold;
                }else{
                    ++numsick;
                    grid[nr][nc]=-1;
                    active.push({nr,nc});
                }
            };

            while(!active.empty()){
                si nr=active.front().first;
                si nc=active.front().second;

                if(N!=0) check(nr+1,nc,N);
                if(S!=0) check(nr-1,nc,S);
                if(W!=0) check(nr,nc+1,W);
                if(E!=0) check(nr,nc-1,E);

                active.pop();
            }

            vals[r][c]=numsick;
        }
    }

    for(auto& vals2 : vals) {
        debVec(vals2);
    }

    si minval=numeric_limits<si>::max();
    for(auto& vals2 : vals) {
        minval=min(*min_element(vals2.begin(), vals2.end()),minval);
    }

    si mincount=0;
    for(auto& vals2 : vals) {
        mincount+=count(vals2.begin(), vals2.end(), minval);
    }

    out<<minval<<"\n"<<mincount<<"\n";
}