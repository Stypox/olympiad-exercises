#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;

#define int int64_t
#define float long double
#define INFTY numeric_limits<int>::max()

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cerr<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cerr<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cerr<<", ";}cerr<<*it;}cerr<<"]";return o;}
void deb(){cerr<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cerr<<t;if(sizeof...(args)!=0){cerr<<"  ";}deb(args...);}
#else
#define deb(...)
#endif
#define out cout
#define in cin



using Direction = uint8_t;
constexpr Direction RIGHT = 1;
constexpr Direction LEFT = 2;
constexpr Direction DOWN = 4;
constexpr Direction UP = 8;
Direction directions[4] {RIGHT,LEFT,DOWN,UP};
Direction tileTypes[11] {0x03,0x05,0x06,0x07,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};
struct TileInfo {
    Direction type;
    int cost = 0;
    int available = 0;
};
using TileGrid = vector<vector<Direction>>;

struct Cell {
    bool is_golden = false;
    int silver_score = 0; // if 0, it's not a silver cell
};
using CellGrid = vector<vector<Cell>>;

char tile_to_id(Direction tileType) {
    switch (tileType) {
        case 0x03: return '3';
        case 0x05: return '5';
        case 0x06: return '6';
        case 0x07: return '7';
        case 0x09: return '9';
        case 0x0A: return 'A';
        case 0x0B: return 'B';
        case 0x0C: return 'C';
        case 0x0D: return 'D';
        case 0x0E: return 'E';
        case 0x0F: return 'F';
    }
    cerr<<"Invalid tile type "<<tileType<<"\n";
    exit(1);
}
Direction id_to_tile(char name) {
    switch (name) {
        case '3': return 0x03;
        case '5': return 0x05;
        case '6': return 0x06;
        case '7': return 0x07;
        case '9': return 0x09;
        case 'A': return 0x0A;
        case 'B': return 0x0B;
        case 'C': return 0x0C;
        case 'D': return 0x0D;
        case 'E': return 0x0E;
        case 'F': return 0x0F;
    }
    cerr<<"Invalid tile name "<<name<<"\n";
    exit(1);
}
Direction inverse_direction(Direction from) {
    assert(from == LEFT || from == RIGHT || from == UP || from == DOWN);
    if (from == LEFT) return RIGHT;
    if (from == RIGHT) return LEFT;
    if (from == UP) return DOWN;
    /*if (from == DOWN)*/ return UP;
}
Direction possible_directions(Direction tileType, Direction from) {
    assert(from == LEFT || from == RIGHT || from == UP || from == DOWN);
    if ((tileType & from) == 0) return 0;
    return tileType ^ from;
}
int delta_x(Direction from) {
    assert(from == LEFT || from == RIGHT || from == UP || from == DOWN);
    if (from == LEFT) return -1;
    if (from == RIGHT) return 1;
    return 0;
}
int delta_y(Direction from) {
    assert(from == LEFT || from == RIGHT || from == UP || from == DOWN);
    if (from == UP) return -1;
    if (from == DOWN) return 1;
    return 0;
}
ostream&operator<<(ostream&o,const TileInfo&p){
    bool found=false;
    for (auto tt:tileTypes) found|=(tt==p.type);
    if(found) o<<tile_to_id(p.type)<<" "<<p.cost<<" "<<p.available;
    return o;
}
ostream&operator<<(ostream&o,const Cell&p){
    if (p.is_golden) o<<"G";
    else if (p.silver_score>0) o<<"S";
    else o<<"_";
    return o;
}



void solve(int W, int H, int G, int S, const array<TileInfo, 16>& tiles, const CellGrid& grid, TileGrid& output);



volatile bool ctrlc = false;
void my_handler(signed){
    ctrlc = true;
}
struct DijktraPos {
    int cost, points, x, y;
    Direction fromDir;
    explicit DijktraPos(Direction _dir) : DijktraPos(0, 0, 0, 0, _dir) {}
    explicit DijktraPos(int _cost, int _points, int _x, int _y, Direction _dir) : cost{_cost}, points{_points}, x{_x}, y{_y}, fromDir{_dir} {}
    bool operator<(const DijktraPos& other) const {
        return tie(cost,points)>tie(other.cost,other.points);
    }
};
ostream&operator<<(ostream&o,const DijktraPos&p){
    o<<"cost="<<p.cost<<",points="<<p.points<<",x="<<p.x<<",y="<<p.y<<",fromDir="<<(int)p.fromDir;
    return o;
}
signed main() {
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);


    int W, H, GN, SM, TL;
    cin >> W >> H >> GN >> SM >> TL;
    deb(W, H, GN, SM, TL);
    vector<pair<int,int>> goldens;
    CellGrid cellGrid(W, vector<Cell>(H, Cell{}));
    TileGrid tileGrid(W, vector<Direction>(H, 0));

    for (int i=0; i<GN; ++i){
        int x,y;
        cin >> x >> y;
        goldens.emplace_back(x,y);
        cellGrid[x][y].is_golden = true;
    }

    for (int i=0; i<SM; ++i){
        int x,y,score;
        cin>>x>>y>>score;
        assert(!cellGrid[x][y].is_golden);
        assert(cellGrid[x][y].silver_score == 0);
        assert(score > 0);
        cellGrid[x][y].silver_score = score;
    }

    array<TileInfo, 16> tiles{};
    for (int i=0; i<16; ++i){
        tiles[i].type=i;
    }
    for (int i=0; i<TL; ++i){
        string id;
        int cost, available;
        cin>>id>>cost>>available;
        Direction tt = id_to_tile(id[0]);
        tiles[tt].cost = cost;
        tiles[tt].available = available;
    }

    solve(W, H, GN, SM, tiles, cellGrid, tileGrid);

    int totPoints = 0;
    for (auto& golden : goldens) {
        priority_queue<DijktraPos> pq;
        vector<vector<pair<int,int>>> bestScore(W, vector<pair<int,int>>(H, pair(INFTY, INFTY)));
        for (auto direction : directions) {
            pq.push(DijktraPos{0, 0, golden.first, golden.second, direction});
        }
        while (!pq.empty()) {
            DijktraPos p = pq.top();
            pq.pop();

            if (p.x<0||p.x>=W||p.y<0||p.y>=H) continue;
            deb(p, cellGrid[p.x][p.y].is_golden, (int)tileGrid[p.x][p.y], (int)p.fromDir);
            if (!cellGrid[p.x][p.y].is_golden && (tileGrid[p.x][p.y]&p.fromDir) == 0) continue;
            pair<int,int> newScore = pair<int,int>{
                p.cost + (cellGrid[p.x][p.y].is_golden ? 0 : tiles[tileGrid[p.x][p.y]].cost),
                p.points + cellGrid[p.x][p.y].silver_score,
            };
            deb(pair(p.cost, p.points), newScore, cellGrid[p.x][p.y].is_golden, (int)tileGrid[p.x][p.y], tiles[tileGrid[p.x][p.y]]);
            if (newScore >= bestScore[p.x][p.y]) continue;
            bestScore[p.x][p.y] = newScore;

            Direction poss = possible_directions(cellGrid[p.x][p.y].is_golden ? 0x0F : tileGrid[p.x][p.y], p.fromDir);
            deb((int)poss);
            for(auto direction : directions) {
                if (poss & direction) {
                    pq.push(DijktraPos{newScore.first, newScore.second, p.x+delta_x(direction), p.y+delta_y(direction), inverse_direction(direction)});
                }
            }
        }

        for (auto& golden : goldens) {
            deb(bestScore[golden.first][golden.second]);
            totPoints += bestScore[golden.first][golden.second].second;
        }
        for (auto& golden : goldens) {
            assert(bestScore[golden.first][golden.second] != pair(INFTY, INFTY));
        }
    }

    assert(totPoints % 2 == 0);
    totPoints /= 2;
    int totCost = 0;
    for (int x=0;x<W;++x){
        for(int y=0;y<H;++y){
            totCost += tiles[tileGrid[x][y]].cost;
        }
    }

    deb(totCost, totPoints, totPoints - totCost);

    return 0;
}
