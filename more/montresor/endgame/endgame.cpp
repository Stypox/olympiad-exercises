#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
using namespace std;

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

struct Cobble{
    int m,e; // 100'000, 100'000
    vector<bool> availableAt;
    vector<int> where;
    int origIndex;

    double emRatio() const {
        return (double)e / (double)m;
    }
};

int N,S,M,C; // 2000, 2000, 10'000, 10'000'000
double R,vmin,vmax; // 5000, 1000, 1000
vector<Cobble> cobbles;
vector<vector<int>> cities;
int NM; //=N+M


constexpr int NONE = -1;
struct Gene{
    int n=NONE, m=NONE;
    bool used;
};

struct Sol{
    vector<Gene> genes;
    double E, G, T;

    Sol() : genes(NM) {
        for(int i=0;i<N;++i){
            if (i!=S){
                genes[NM-i-1].n = i;
            }
        }
        assert(genes[0].n==NONE);
        genes[0].n=S;
        for(int i=0;i<M;++i){
            genes[NM-i-1].m = i;
        }
    }

    void evaluate() {
        G = 0;
        T = 0;
        int W = 0;
        int n = S;
        assert(genes[0].n == S);

        for(auto& gene:genes){
            gene.used=false;
            if(gene.n != NONE){
                T += cities[n][gene.n] / (vmax - W * (vmax - vmin) / C);
                n = gene.n;

                if(gene.m != NONE){
                    auto& cobble=cobbles[gene.m];
                    if(W + cobble.m <= C && cobble.availableAt[gene.n]) {
                        W += cobble.m;
                        G += cobble.e;
                        gene.used = true;
                    }
                }
            }
        }

        T += cities[n][S] / (vmax - W * (vmax - vmin) / C);
        E = G - R * T;
    }

    void print() {
        out << scientific << setprecision(10) << E << " ";
        out << scientific << setprecision(10) << G << " ";
        out << scientific << setprecision(10) << T << "\n";
        vector<int> p(M,NONE);
        for(auto& gene:genes){
            if(gene.used){
                p[cobbles[gene.m].origIndex]=gene.n;
            }
        }
        for(int m=0;m<M;++m){
            if(m!=0){
                out<<" ";
            }
            out<<p[m];
        }
        out<<"\n";
        for(auto& gene:genes){
            if(gene.n!=NONE){
                out<<gene.n<<" ";
            }
        }
        out<<S<<"\n";
        out<<"***"<<endl;
    }

    bool operator<(const Sol& other) const {
        return E < other.E;
    }
};


static volatile sig_atomic_t timeLimitExceeded = 0;
void setupTimeLimit(){
    struct sigaction new_action;
    new_action.sa_handler = [](int) {
        timeLimitExceeded = 1;
    };
    sigemptyset(&new_action.sa_mask);
    sigaddset(&new_action.sa_mask, SIGXCPU);
    new_action.sa_flags = 0;
    sigaction(SIGXCPU,&new_action,NULL);

    struct rlimit limit;
    getrlimit(RLIMIT_CPU, &limit);
    limit.rlim_cur = 5;
    setrlimit(RLIMIT_CPU, &limit);
}

signed main() {
    setupTimeLimit();

    in>>N>>S>>M>>C>>R>>vmin>>vmax;
    NM=N+M;

    cobbles.resize(M);
    for(int m=0;m<M;++m){
        in>>cobbles[m].m>>cobbles[m].e;
        cobbles[m].origIndex=m;
    }
    for(auto& cobble:cobbles){
        int L;
        in>>L;
        cobble.availableAt.resize(N);
        for(int l=0;l<L;++l){
            int v;
            in>>v;
            cobble.availableAt[v] = true;
            cobble.where.push_back(v);
        }
    }
    /*sort(cobbles.begin(), cobbles.end(), [](const Cobble& a, const Cobble& b) {
        return a.emRatio() > b.emRatio();
    });*/
    deb(cities);
    for(auto& cobble:cobbles){
        deb(cobble.origIndex, cobble.e, cobble.m, cobble.availableAt);
    }

    cities.resize(N, vector<int>(N,0));
    for(int a=1;a<N;++a){
        for(int b=0;b<a;++b){
            int w;
            in>>w;
            cities[a][b] = w;
            cities[b][a] = w;
        }
    }

    vector<Sol> sols;
    {
        Sol sol;
        sol.evaluate();
        sols.resize(3, sol);
    }


    while(timeLimitExceeded == 0) {
        int s=rand()%sols.size();
        Sol newSol = sols[s];

        int K=rand()%10;
        for(int k=0;k<K;++k){
            int c=rand();
            if(c>RAND_MAX/2){
                vector<int> unsatisfied, noM, noN;
                for(int a=1;a<newSol.genes.size();++a){
                    const Gene& gene=newSol.genes[a];
                    if(gene.m==NONE && gene.n==NONE) {
                    }else if(gene.m==NONE) {
                        noM.push_back(a);
                    }else if(gene.n==NONE) {
                        noN.push_back(a);
                    }else if(!cobbles[gene.m].availableAt[gene.n]){
                        unsatisfied.push_back(a);
                    }
                }

                if (noN.size() > 0 && noM.size() > 0 && rand() > RAND_MAX/2) {
                    int a=noN[rand()%noN.size()];
                    int b=noM[rand()%noM.size()];
                    swap(newSol.genes[a].m, newSol.genes[b].m);
                }
                if (unsatisfied.size() > 1 && rand() > RAND_MAX/2) {
                    int a=unsatisfied[rand()%unsatisfied.size()];
                    int b=unsatisfied[rand()%unsatisfied.size()];
                    swap(newSol.genes[a].n, newSol.genes[b].n);
                }
                continue;
            }

            int a=rand()%(NM-1)+1;
            int b=rand()%(NM-1)+1;
            if(c > RAND_MAX/6*2){
                swap(newSol.genes[a],   newSol.genes[b]  );
            } else if (c > RAND_MAX/6) {
                swap(newSol.genes[a].n, newSol.genes[b].n);
            } else {
                swap(newSol.genes[a].m, newSol.genes[b].m);
            }
        }

        newSol.evaluate();
        if (newSol.E >= sols[s].E) {
            swap(sols[s], newSol);
        }
    }

    max_element(sols.begin(), sols.end())->print();
    return 0;
}
