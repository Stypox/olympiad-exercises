#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=string, class S=string> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#else
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=string, class S=string> constexpr void debc(const T&, P="", S="") {}
#endif

struct Stand {
    int bellezza;
    bool animale, guida;
};

int32_t main() {
	int N, M;
    in>>N>>M;

    vector<int> E(M);
    for(int m=0;m<M;++m) {
        in>>E[m];
    }

    vector<Stand> stands(N);
    for(int n=0;n<N;++n){
        in>>stands[n].bellezza;
        int a,g;
        in>>a>>g;
        stands[n].animale = (a==1);
        stands[n].guida = (g==1);
    }

    int k = numeric_limits<int>::max();
    int maxAG[2][2] {{-1, -1}, {-1, -1}};
    int minAG[2][2] {{k, k}, {k, k}};
    int maxAn[2] = {-1, -1};
    int count0011[2] = {0, 0};
    for(Stand& stand:stands){
        maxAG[stand.animale][stand.guida] = max(maxAG[stand.animale][stand.guida], stand.bellezza);
        minAG[stand.animale][stand.guida] = min(minAG[stand.animale][stand.guida], stand.bellezza);
        maxAn[stand.animale] = max(maxAn[stand.animale], stand.bellezza);

        if (stand.animale == stand.guida) {
            count0011[stand.guida]++;
        }
    }

    for(int& e:E){
        int bellezzaPartenza = stands[e].bellezza;
        bool animalePartenza = stands[e].animale;
        bool guidaPartenza = stands[e].guida;

        bool ris;
        if (maxAn[guidaPartenza] > maxAn[!guidaPartenza]) {
            ris=guidaPartenza;
        } else {
            if (guidaPartenza != animalePartenza) {
                if (maxAG[guidaPartenza][guidaPartenza] > bellezzaPartenza) {
                    ris = guidaPartenza;
                } else {
                    ris = !guidaPartenza;
                }
            } else {
                if (minAG[!animalePartenza][guidaPartenza] != -1 && minAG[!animalePartenza][guidaPartenza] < bellezzaPartenza) {
                    ris = guidaPartenza;
                } else if (count0011[guidaPartenza] > 1) {
                    ris = guidaPartenza;
                } else {
                    ris = !guidaPartenza;
                }
            }
        }

        out<<(ris ? 1 : 0)<<" ";
    }
}
