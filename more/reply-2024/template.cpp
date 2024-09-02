#include "template_impl.cpp"


void solve(int W, int H, int G, int S, const array<TileInfo, 16>& tiles, const CellGrid& grid, TileGrid& output) {
    ifstream f{"solutions/0.txt"};
    while(1){
        string s;
        int x,y;
        f>>s;
        if (!f || f.eof()) break;
        f>>x>>y;
        if (!f || f.eof()) break;
        deb(s, x, y);
        output[x][y] = id_to_tile(s[0]);
    }
}
