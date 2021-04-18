#include<bits/stdc++.h>
using namespace std;
using ll=long long;

struct arco {
    int to, w8;
};

struct nodo {
   array<int, 20> antenati;
   array<ll, 20> dist;
   array<ll, 20> minarco;

   vector<arco> figli;
   int altezza;
};

vector<nodo> albero;

int lift(int v, int h) {
   for(int e=20; e>=0; e--) {
       if(h & (1<<e)) {
          v = albero[v].antenati[e];
       }
   }
   return v;
}

ll dist(int v, int h) {
   ll res = 0;
   for(int e=20; e>=0; e--) {
      if(h & (1<<e)) {
         res += albero[v].dist[e];
         v = albero[v].antenati[e];
      }
   }
   return res;
}

ll minarco(int v, int h) {
   ll res = numeric_limits<ll>::max();
   for(int e=20; e>=0; e--) {
      if(h & (1<<e)) {
         res = min(res, albero[v].minarco[e]);
         v = albero[v].antenati[e];
      }
   }
   return res;
}

int lca(int u, int v) {
   int hu=albero[u].altezza, hv=albero[v].altezza;
   if (hu>hv) {
      u=lift(u, hu-hv);
   } else if (hv>hu) {
      v=lift(v, hv-hu);
   }

   if(u==v) {
      return u;
   }

   for(int e=19; e>=0; e--) {
      if(albero[u].antenati[e]!=albero[v].antenati[e]) {
         u=albero[u].antenati[e];
         v=albero[v].antenati[e];
      }
   }
   return albero[u].antenati[0];
}

void inizia(int N, int, int A[], int B[], int C[]) {
   albero.resize(N);
   for(int t=0;t<N-1;++t) {
      albero[A[t]].figli.push_back({B[t], C[t]});
      albero[B[t]].figli.push_back({A[t], C[t]});
   }

   function<void(int, int, int, int)> dfsTree = [&](int i, int d, int p, int h) {
      albero[i].antenati[0] = p;
      albero[i].dist[0] = d;
      albero[i].minarco[0] = d;

      albero[i].altezza = h;
      albero[i].figli.erase(remove_if(albero[i].figli.begin(), albero[i].figli.end(), [&p](const arco& a) { return a.to == p; }), albero[i].figli.end());
      for(auto [to, w8] : albero[i].figli) {
         dfsTree(to, w8, i, h+1);
      }
   };

   dfsTree(0, 0, 0, 0);
   albero[0].minarco[0] = numeric_limits<ll>::max();

   for(int e=1;e<20;++e) {
      for(int i=0; i<N; i++) {
         int half = albero[i].antenati[e-1];
         albero[i].antenati[e] = albero[half].antenati[e-1];
         albero[i].dist[e] = albero[i].dist[e-1] + albero[half].dist[e-1];
         albero[i].minarco[e] = min(albero[i].minarco[e-1], albero[half].minarco[e-1]);
      }
   }
}

long long int distanza1(int u, int v) {
   int ca = lca(u, v);
   return albero[u].altezza + albero[v].altezza - 2*albero[ca].altezza;
}

long long int distanza2(int u, int v) {
   int ca = lca(u, v);
   int hca = albero[ca].altezza;
   return dist(u, albero[u].altezza-hca) + dist(v, albero[v].altezza-hca);
}

long long int minimo(int u, int v) {
   int ca = lca(u, v);
   int hca = albero[ca].altezza;
   return min(minarco(u, albero[u].altezza-hca), minarco(v, albero[v].altezza-hca));
}

long long int massimo(int u, int v) {
   return 123456789123ll+u-v;
}
