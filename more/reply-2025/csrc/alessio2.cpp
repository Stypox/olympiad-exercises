#include"template.cpp"
#include <climits>
#include <cstdlib>
#include <iostream>
#include <vector>
vector<vector<int>> solve(
    int D,
    vector<Resource>& resources,
    vector<Turn>& turns,
    vector<vector<int>> init
){
    srand(time(0));
    vector<vector<int>> c=init;
    
    auto [best_score, dummy] = eval(D, resources, turns, c);
    vector<vector<int>> best=c;
    deb("res", best_score);
    vector<int> last_profitti;
    while (!ctrlc){
        c=best;
        int moves = 1+rand()%10;
        int argmin =INT_MAX;
        int argpos = rand() % turns.size();
        if (last_profitti.size()==turns.size()) {
            for(int j=0; j<100; j++){
                int i = rand()%turns.size();
                if(last_profitti[i]<argmin){
                    argmin=last_profitti[i];
                    argpos=i;
                }
            }
        }
        argpos=max(argpos-6, (int)0);
        bool solorimosso=true;
        bool modificato=false;
        for(int i=0; i<moves; i++){
            
            if(rand()%2){
                int turno = rand()%6+argpos;
                int val = rand()%resources.size();
                c[turno].push_back(val);
                solorimosso=false;
                modificato=true;
            }else{
                int turno = rand()%6+argpos;
                if(c[turno].size()==0){
                    continue;
                }
                modificato=true;
                int indice = rand()%(c[turno].size());
                c[turno].erase(c[turno].begin()+indice);
            }
        }
        if(!modificato) continue;
        auto [ev, profitti]= eval(D, resources, turns, c);
        if (ev>best_score || (ev==best_score && solorimosso)){
            last_profitti=profitti;
            cerr<<"found better "<<best_score<<endl;
            best_score=ev;
            best=c;
        }
    }
    
    return best;
}


