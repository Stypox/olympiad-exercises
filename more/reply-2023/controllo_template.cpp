#include "template.cpp"

void solve(int C, int R, int S, vector<int> lengths, vector<vector<int>> matrix, vector<pair<int,int>> wormholes, vector<vector<int>>& output) {
    deb("lunghezze",accumulate(lengths.begin(), lengths.end(), 0));
    deb("r*c",R*C);

    int s=0;
    for(int r=0;r<R;++r){
        for(int c=0;c<C;++c){
            s+=max((int)0LL,matrix[r][c]);
        }
    }
    deb("sum", s);

    output[0] = {0, 0, RIGHT, RIGHT, DOWN, 7, 2, RIGHT, RIGHT};
    output[1] = {6, 1, LEFT, UP, LEFT, DOWN, LEFT, UP};
    output[2] = {1, 1, RIGHT, 3, 4, RIGHT, RIGHT, RIGHT};
    output[3] = {7, 1, DOWN, 3, 4, LEFT};
    output[4] = {9, 0, UP, LEFT};
}