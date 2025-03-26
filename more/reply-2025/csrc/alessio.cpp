#include"template.cpp"
#include <vector>
vector<vector<int>> solve(int D, vector<Resource>& resources, vector<Turn>& turns){
    vector<vector<int>> c;
    for(int i=0; i<turns.size(); i++){
        vector<int> v(1,1);
        //v.push_back(rand()%resources.size());
        //v.push_back(1);
        c.push_back(v);
    }
    int64_t ev = eval(D, resources, turns, c);
    deb("res", ev);
    return c;
}


