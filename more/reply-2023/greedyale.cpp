#include"template.cpp"

vector<vector<bool>> occupati;
int r, c;
vector<vector<int>> valori;
vector<int> test(int x, int y, int length);


int get(int x, int y){
    x=(x+r)%r;
    y=(y+c)%c;
    cout<<x<<" "<<y<<endl;
    if(occupati[y][x]==false){
        return valori[y][x];
    }else{
        return numeric_limits<int>::min();
    }
    
}


void solve(int C, int R, int S, vector<int> lengths, vector<vector<int>> matrix, vector<pair<int,int>> wormholes, vector<vector<int>>& output){
    r=R;
    c=C;
    occupati.resize(matrix.size());
    valori.resize(matrix.size());
    for(int i=0; i<matrix.size(); i++){
        occupati[i].resize(matrix[i].size());
        valori[i]=matrix[i];
    }
    output.resize(S);
    for(int i=0; i<S; i++){
        int x= rand()%C;
        int y = rand()%R;
        while((get(x, y)==numeric_limits<int>::min()) || matrix[y][x]!=WORMHOLE){
            x= rand()%C;
            y = rand()%R;
        }
        output[i] = test(x, y, lengths[i]);
    }
}
/*#define WORMHOLE 999999
#define UP 1000001
#define DOWN 1000002
#define LEFT 1000003
#define RIGHT 1000004
*/


int whormy=0;
class action{
    public:
        int point=0;
        vector<int> actions;
        int xi, yi;
        action(int x, int y, int m){
            if(m==UP){
                point = get(x, y-1);
            }else if(m==DOWN){
                point = get(x, y+1);
            }else if(m==LEFT){
                point = get(x-1, y);
            }else {
                point = get(x+1, y);
            }
            xi=x;
            yi=y;
            if(point ==WORMHOLE){
                whormy=m;
                point=0;
            }
            actions.push_back(m);
        }

        bool operator<(action inp) const {
            return this->point<inp.point;
        }
};

vector<action> single_test(int x, int y){
    vector<action> tmp;

    tmp.push_back(action(x, y, UP));
    tmp.push_back(action(x, y, DOWN));
    tmp.push_back(action(x, y, LEFT));
    tmp.push_back(action(x, y, RIGHT));

    return tmp;
}

action get_max(vector<action> tmp, int xs, int ys){
    action best(xs, ys, UP);
    for(int i=0; i<4; i++){
        if(best<tmp[i]){
            best=tmp[i];
        }
    }
    return best;
}

vector<int> test(int x, int y, int length){
    pair<int, int> start(x, y);
    //pair<int, int> end(x, y);
    occupati[y][x]=true;
    cout<<x<<" "<<y<<endl;
    vector<int> sol;
    sol.push_back(x);
    sol.push_back(y);
    for(int i=1; i<length; i++){
        action bestStart = get_max(single_test(start.first, start.second), start.first, start.second);
        sol.push_back(bestStart.actions[0]);
        occupati[bestStart.yi][bestStart.xi]=true;
        start = make_pair(bestStart.xi, bestStart.yi);
        //action bestEnd = get_max(single_test(end.first, end.second), end.first, end.second);
        /*if(bestStart<bestEnd){
            sol.push_back(sol.end(), bestEnd.actions.begin());
        }else{
            
        }*/
    }
    return sol;
}