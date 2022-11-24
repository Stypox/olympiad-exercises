#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif
#define cout Do not use cout!!!
#define cin Do not use cin!!!

constexpr int LCA_SIZE = 16;

struct Node {
    vector<int> to;
    int tin=-1, tmin, mesh=-1;
};

struct MeshEdge {
    int fromNode, toNode, toMesh;
};

struct MeshParent {
    int childNode, ancestorNode, ancestorMesh, length;
};

struct MeshNode {
    vector<MeshEdge> to;
    array<MeshParent, LCA_SIZE> par;
    int depth;
};

signed main() {
    int N,M,Q;
    in>>N>>M>>Q;

    vector<Node> nodes(N);
    for(int m=0;m<M;++m){
        int a, b;
        in>>a>>b;
        nodes[a].to.push_back(b);
        nodes[b].to.push_back(a);
    }

    int t=0;
    stack<int> s;
    vector<MeshNode> meshes;
    vector<pair<int,int>> conns;
    function<void(int,int)> findMeshes = [&](int i, int prev) {
        if (nodes[i].tin != -1) return;

        nodes[i].tin = t;
        nodes[i].tmin = t;
        t++;
        s.push(i);
        for(auto e:nodes[i].to){
            if (e!=prev) {
                findMeshes(e,i);
                if (nodes[e].mesh == -1) {
                    nodes[i].tmin = min(nodes[i].tmin, nodes[e].tmin);
                } else {
                    conns.push_back({e,i});
                }
            }
        }

        if (nodes[i].tin == nodes[i].tmin) {
            while(!s.empty()) {
                int e=s.top();
                s.pop();

                nodes[e].mesh=meshes.size();
                if(e==i) break;
            }
            meshes.emplace_back();
        }
    };
    findMeshes(0,-1);

    for(int i=0;i<nodes.size();++i){
        assert(nodes[i].mesh != -1);
        deb(i,":",nodes[i].mesh,nodes[i].tmin,nodes[i].to);
    }
    deb(meshes.size(), conns);

    for(auto [a,b] : conns) {
        meshes[nodes[a].mesh].to.push_back(MeshEdge{a,b,nodes[b].mesh});
        meshes[nodes[b].mesh].to.push_back(MeshEdge{b,a,nodes[a].mesh});
    }
    conns.clear();

    function<void(MeshEdge&,int,int)> findTree = [&](MeshEdge& i, int par, int depth) {
        meshes[i.toMesh].par[0] = MeshParent{i.toNode, i.fromNode, par, 1};
        meshes[i.toMesh].depth = depth;
        for(auto& e : meshes[i.toMesh].to) {
            if (e.toMesh != par) {
                findTree(e, i.toMesh, depth+1);
            }
        }
    };
    MeshEdge undef{-1,-1,0};
    findTree(undef,0,0);
    meshes[0].par[0].length=0;

    auto merge = [](const MeshParent& a, const MeshParent& b) {
        MeshParent toUpdate;
        toUpdate.ancestorMesh = b.ancestorMesh;
        toUpdate.ancestorNode = (b.ancestorNode == -1 ? a.ancestorNode : b.ancestorNode);
        toUpdate.childNode = a.childNode;
        if (b.ancestorNode == -1) {
            toUpdate.length = a.length;
        } else {
            toUpdate.length = a.length + b.length + (a.ancestorNode == b.childNode ? 0 : 1);
        }
        return toUpdate;
    };

    for (int i=1;i<LCA_SIZE;++i) {
        for (int j=0;j<meshes.size();++j) {
            meshes[j].par[i] = merge(meshes[j].par[i-1], meshes[meshes[j].par[i-1].ancestorMesh].par[i-1]);
        }
    }

    deb("i", "j", "childNode", "ancestorNode", "ancestorMesh", "length");
    deb(" ", "i", "j", "  ch", "an", " me", "l");
    for (int j=1;j<meshes.size();++j) {
        for(int i=0;i<4;++i){
            deb("(", i, j, "", meshes[j].par[i].childNode, meshes[j].par[i].ancestorNode, "", meshes[j].par[i].ancestorMesh, meshes[j].par[i].length);
        }
    }

    auto lift = [&](MeshParent a, int delta) {
        int i=0;
        while(delta!=0){
            if(delta&1) {
                a = merge(a, meshes[a.ancestorMesh].par[i]);
            }
            delta/=2;
            i++;
        }
        return a;
    };

    #ifdef TABLE
    Q=N*N;
    #endif
    for (int q=0;q<Q;++q){
        int a,b;
        #ifdef TABLE
        a=q%N;
        b=q/N;
        #else
        in>>a>>b;
        #endif

        int x = nodes[a].mesh,y = nodes[b].mesh;
        if (meshes[x].depth < meshes[y].depth) { swap(x,y); swap(a,b); }
        int delta = meshes[x].depth - meshes[y].depth;
        deb("a,b", a,b, "  x,y", x,y, "  hx-hy=delta", meshes[x].depth,meshes[y].depth,delta);
        MeshParent liftedx=lift(MeshParent{a,a,x,0}, delta);
        deb("liftedx", liftedx.length);

        int p;
        if (liftedx.ancestorMesh == y) {
            p = y;
        } else {
            int px=liftedx.ancestorMesh, py=y;
            for(int i=LCA_SIZE-1;i>=0;--i){
                if(meshes[px].par[i].ancestorMesh != meshes[py].par[i].ancestorMesh) {
                    px=meshes[px].par[i].ancestorMesh;
                    py=meshes[py].par[i].ancestorMesh;
                }
            }

            assert(meshes[px].par[0].ancestorMesh == meshes[py].par[0].ancestorMesh);
            p = meshes[px].par[0].ancestorMesh;
        }

        liftedx = lift(MeshParent{a,a,x,0}, meshes[x].depth - meshes[p].depth);
        MeshParent liftedy = lift(MeshParent{b,b,y,0}, meshes[y].depth - meshes[p].depth);
        swap(liftedy.ancestorNode, liftedy.childNode);
        deb(liftedx.length, liftedy.length, x, y, meshes[x].depth - meshes[p].depth, meshes[y].depth - meshes[p].depth);
        MeshParent r = merge(liftedx, liftedy);

        #ifdef TABLE
        out<<r.length<<(q%N == N-1 ? "\n" : " ");
        #else
        out<<r.length<<"\n";
        #endif
    }
}
