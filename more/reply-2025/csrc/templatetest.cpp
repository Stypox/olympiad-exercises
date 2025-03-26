#include "template.cpp"

vector<vector<int>> solve(
    int D,
    vector<Resource>& resources,
    vector<Turn>& turns
) {
    int i=0;
    for(auto& res:resources) {
        if (res.L < 2) {
            deb(res);
        }
        if (i != res.I) {
            deb(i, res);
        }
        i+=1;
    }
    return {}; vector<vector<int>>(turns.size());
}