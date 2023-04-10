#include "template.cpp"
constexpr int tries=10;

struct Snake {
    int length;
    int index;
    vector<int> moves;
};


void solve(int C, int R, int S, vector<int> lengths, vector<vector<int>> matrix, vector<pair<int,int>> wormholes, vector<vector<int>>& output) {
    std::mt19937 rng(0);
    std::uniform_int_distribution<std::mt19937::result_type> randomR(0,R-1);
    std::uniform_int_distribution<std::mt19937::result_type> randomC(0,C-1);
    std::uniform_int_distribution<std::mt19937::result_type> randomWh(0,wormholes.size()-1);

    auto move = [&](int r, int c, int m) -> pair<int,int> {
        if (m == UP) {
            return {(r+R-1)%R,c};
        } else if (m == DOWN) {
            return {(r+R+1)%R,c};
        } else if (m == RIGHT) {
            return {r,(c+1+C)%C};
        } else if (m == LEFT) {
            return {r,(c-1+C)%C};
        } else {
            assert(false);
        }
    };

    vector<Snake> snakes;
    for(int s=0;s<S;++s){
        snakes.push_back({lengths[s], s, vector<int>()});
    }

    sort(snakes.begin(), snakes.end(), [&](auto& a, auto& b) { return a.length > b.length; });

    vector<vector<bool>> used(R, vector<bool>(C,false));
    for(auto& [length, index, moves] : snakes) {
        for(int t=0;t<tries;++t){
            int r,c;
            while(true){
                r=randomR(rng);
                c=randomC(rng);
                if(!used[r][c] && matrix[r][c] != WORMHOLE) {
                    break;
                }
            }
            moves.push_back(c);
            moves.push_back(r);
            used[r][c]=true;

            int usedl=1;
            bool errore=false;
            vector<vector<bool>> usedcopy = used;
            int val=0;

            while(usedl<length){
                int bestm=0;
                int best=numeric_limits<int>::min();
                for (auto m : {LEFT, RIGHT, UP, DOWN}) {
                    auto [nr, nc] = move(r, c, m);
                    if (!usedcopy[nr][nc] && (usedl < length-2 || matrix[nr][nc] != WORMHOLE)) {
                        if (matrix[nr][nc] == WORMHOLE && 0 > best) {
                            best = 0;
                            bestm = m;
                        } else if (matrix[nr][nc] > best) {
                            best = matrix[nr][nc];
                            bestm = m;
                        }
                    }
                }

                if (bestm == 0) {
                    errore=true;
                    break;
                }

                usedl+=1;
                auto [nr, nc] = move(r, c, bestm);
                r=nr;
                c=nc;
                moves.push_back(bestm);

                if (matrix[r][c] == WORMHOLE) {
                    usedl++;
                    assert(usedl<length);
                    moves.push_back(c);
                    moves.push_back(r);
                } else {
                    assert(used[nr][nc] == false);
                    assert(usedcopy[nr][nc] == false);
                    usedcopy[r][c] = true;
                    val += matrix[r][c];
                }
            }
            assert(errore || moves.back() == UP || moves.back() == DOWN || moves.back() == LEFT || moves.back() == RIGHT);

            if (errore || val <= 0) {
                moves.resize(0);
                continue;
            }
            used = usedcopy;
            break;
        }
    }

    for(auto& [length, index, moves] : snakes) {
        output[index] = moves;
    }
}