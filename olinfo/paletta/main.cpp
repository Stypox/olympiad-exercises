#include<bits/stdc++.h>
using si = int64_t;
using namespace std;

ifstream in{"input.txt"};
ofstream out{"output.txt"};
using pii = pair<si,si>;

struct FT {
    constexpr static si lsOne(si x) { return x & (-x); }

    vector<si> data;
    FT(si N) : data(N+1, 0) {}

    si query(si i) {
        si s=0;
        for(; i!=0; i-=lsOne(i)) {
            s+=data[i];
        }
        return s;
    }

    void update(si i, si delta) {
        ++i;
        for(; i<data.size(); i+=lsOne(i)) {
            data[i]+=delta;
            //cout<<i<<"\n";
        }
    }
};

si ways(const vector<si>& vec) {
    FT numeri(vec.size());
    vector<pii> minimi;
    minimi.reserve(vec.size());
    for(si n=0;n<vec.size();++n){
        numeri.update(n,1);
        minimi.push_back(pair<si,si>{vec[n],n});
    }

    si res=0;
    sort(minimi.begin(), minimi.end(), [](pii& a, pii& b){ return a.first < b.first; });
    for(auto&& minimo:minimi) {
        numeri.update(minimo.second, -1);
        res += numeri.query(minimo.second);
    }
    
    return res;
}

long long paletta_sort(int N, int V[]) {
    vector<si> even,odd;
    for(si n=0;n<N;++n){
        if ((n%2) != (V[n]%2)) return -1;

        if (n%2) {
            odd.push_back(V[n]);
        } else {
            even.push_back(V[n]);
        }
    }
    return ways(even)+ways(odd);
}
/*
int main() {
    int a[] = {2, 0, 4, 3, 1};
    cout<<paletta_sort(5,a)<<"\n";
}*/
/*
int main() {
    int a[] = {2,3,0,5,4,1};
    cout<<paletta_sort(6,a)<<"\n";
}*/
/*
int main() {
    int N;
    in>>N;

    vector<int> A(N);
    for(auto& a:A) {
        in>>a;
        //--a;
    }
    cout<<paletta_sort(N,A.data())<<"\n";
}*/