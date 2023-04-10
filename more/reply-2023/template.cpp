#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
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
#define out cout
#define in cin

#define WORMHOLE 999999
#define UP 1000001
#define DOWN 1000002
#define LEFT 1000003
#define RIGHT 1000004
#define INVALID_LENGTH -1000001
#define MALFORMER_OUTPUT -1000002
#define NOT_WORMHOLE -1000003
#define INVALID_CELL_A -1000004
#define INVALID_CELL_B -1000005
#define INVALID_CELL_C -1000006


void solve(int C, int R, int S, vector<int> lengths, vector<vector<int>> matrix, vector<pair<int,int>> wormholes, vector<vector<int>>& output);

int valuta(int C, int R, int S, const vector<int>& lengths, const vector<vector<int>>& matrix, const vector<vector<int>>& output) {
    vector<vector<bool>> used(R, vector<bool>(C, false));
    for (int s=0; s<S; ++s){
        if (output[s].size() == 0) {
            continue;
        }

        if (output[s].size() < 2) {
            deb(s, output[s].size());
            return INVALID_LENGTH;
        }

        int moves=1;
        int c=output[s][0],r=output[s][1];
        if (matrix[r][c] == WORMHOLE || used[r][c]){
            return INVALID_CELL_A;
        }
        used[r][c] = true;

        for(int i=2;i<output[s].size();i++){
            if (output[s][i]==UP){
                r=(r+R-1)%R;
            } else if (output[s][i]==DOWN){
                r=(r+1)%R;
            } else if (output[s][i]==LEFT){
                c=(c+C-1)%C;
            } else if (output[s][i]==RIGHT){
                c=(c+1)%C;
            } else if (matrix[r][c]==WORMHOLE) {
                if (i == output[s].size()-1) {
                    deb(r, c, s, i);
                    return INVALID_LENGTH;
                }
                c=output[s][i];
                r=output[s][i+1];
                i++;
                moves++;

                if(r >= UP){
                    deb(r, c, s, i);
                    return MALFORMER_OUTPUT;
                }

                if (matrix[r][c] != WORMHOLE) {
                    deb(r, c, s, i, matrix);
                    return NOT_WORMHOLE;
                }
                continue;
            } else {
                deb(r, c, s, i);
                return MALFORMER_OUTPUT;
            }

            moves++;
            if (matrix[r][c]!=WORMHOLE && used[r][c]) {
                deb(r, c, s, i);
                return INVALID_CELL_B;
            }
            used[r][c] = true;
        }

        if (moves != lengths[s]) {
            deb(r, c, s);
            return INVALID_LENGTH;
        }
        if (matrix[r][c] == WORMHOLE){
            deb(r, c, s);
            return INVALID_CELL_C;
        }
        used[r][c] = true;
    }

    int res=0;
    for(int r=0;r<R;++r){
        for(int c=0;c<C;++c){
            if (used[r][c] && matrix[r][c] != WORMHOLE) {
                res += matrix[r][c];
            }
        }
    }

    return res;
}

bool ctrlc = false;
void my_handler(signed s){
    ctrlc = true;
}


signed main() {
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);

    int C, R, S;
    in >> C >> R >> S;

    vector<int> lengths(S);
    for (int s=0; s<S; ++s){
        in >> lengths[s];
    }

    vector<vector<int>> matrix(R, vector<int>(C));
    vector<pair<int,int>> wormholes;
    for (int r=0; r<R; ++r){
        for(int c=0; c<C; ++c){
            int v;
            in >> v;
            if (!in) {
                in.clear();
                char c;
                in >> c;
                v = WORMHOLE;
                wormholes.emplace_back(r, c);
            }
            matrix[r][c] = v;
        }
    }

    vector<vector<int>> output(S);
    solve(C, R, S, lengths, matrix, wormholes, output);
    int res = valuta(C, R, S, lengths, matrix, output);
    cerr << res << endl;

    for (int s=0; s<S; ++s){
        for (auto v : output[s]){
            if (v==UP){
                out << "U";
            } else if (v==DOWN){
                out << "D";
            } else if (v==LEFT){
                out << "L";
            } else if (v==RIGHT){
                out << "R";
            } else {
                out << v;
            }
            out << " ";
        }
    }
}
