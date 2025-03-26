#include"template.cpp"
#include <bits/stdc++.h>


bool compareByU(const Resource &a, const Resource &b)
{
    return a.U > b.U;
}

vector<vector<int>> solve(int D, vector<Resource>& resources, vector<Turn>& turns){
    vector<vector<int>> c;

    // greedy in cui compro le risorse che powerano più edifici, stando in 1/3 budget iniziale ogni turno
    sort(resources.begin(), resources.end(), compareByU);

    for(auto r : resources){
        deb("id", r.I, "A", r.A, "U", r.U);
    }

    for(int i=0; i<turns.size(); i++){
        int spent = 0, bought = 0;

        vector<int> v(0);
deb("\nturno", i);
        for(auto r : resources){

            if(r.A < D/3 && spent + r.A + r.P < D && rand()%2 == 1){
                spent += r.A; bought++;
                v.push_back(r.I);
                deb("\tid", r.I, "A", r.A);
            }

            if(spent >= D/3 || bought >= 25){
                break;
            }
        }

        c.push_back(v);
    }
    deb(c);
    int64_t ev = eval(D, resources, turns, c);
    deb("res", ev);
    return c;
}