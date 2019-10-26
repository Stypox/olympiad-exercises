#include<bits/stdc++.h>
using si = int64_t;
using namespace std;

ifstream in{"input.txt"};
ofstream out{"output.txt"};

struct Node {
    si cost;
    vector<si> conn;
};
struct Res {
    si with, without;
    vector<si> pwith, pwithout;
};

vector<Node> nodes;

void rem(vector<si>& vec, si val) {
    vec.erase(remove(vec.begin(),vec.end(),val), vec.end());
}
void add(vector<si>& vec, const vector<si>& other) {
    vec.insert(vec.end(), other.begin(), other.end());
}

Res rec(si n) {
    Res res;
    res.without=0; res.with=nodes[n].cost;
    res.pwith.push_back(n);

    for(auto con : nodes[n].conn) {
        rem(nodes[con].conn, n);
        Res r = rec(con);

        res.without+=r.with;
        add(res.pwithout, r.pwith);

        if (r.with < r.without) {
            res.with+=r.with;
            add(res.pwith, r.pwith);
        } else {
            res.with+=r.without;
            add(res.pwith, r.pwithout);
        }
    }

    return res;
}

int main() {
    si N;
    in>>N;
    
    nodes.resize(N);
    for(auto&& node:nodes){
        in>>node.cost;
    }

    for(si n=0;n<(N-1);++n) {
        si a,b;
        in>>a>>b;
        --a; --b;

        nodes[a].conn.push_back(b);
        nodes[b].conn.push_back(a);
    }

    Res res = rec(0);
    if (res.with < res.without) {
        out<<res.pwith.size()<<"\n";
        for(auto p:res.pwith){
            out<<p+1<<" ";
        }
        out<<"\n";
    }else{
        out<<res.pwithout.size()<<"\n";
        for(auto p:res.pwithout){
            out<<p+1<<" ";
        }
        out<<"\n";
    }
}