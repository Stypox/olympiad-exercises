#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int i, w;
    Edge(int ii, int ww) : i{ii}, w{ww} {}
};

struct Node {
    vector<Edge> neighbors;
    vector<Edge> children;
    int parent=0;
    int depth=0;

    int maxDist=0;
    int maxChi=0;
    int maxDist2=0;

    int far=0;

    int controlledNodes=0;
    int subtreeRoot=-1;
};

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
void printTree(const vector<Node>& nodes, int i, int indent=0) {
    const Node& n = nodes[i];
    for(int j=0;j<indent;++j)cout<<" ";
    cout<<i<<" | "<<n.far;
    if (n.children.size() > 0) cout<<" ->\n";
    for(int j=0;j<(int)n.children.size();++j){
        if (j!=0) cout<<"\n";
        printTree(nodes, n.children[j].i, indent+3);
    }
    if (indent == 0) cout<<"\n\n";
};
#else
#define deb(...)
#define printTree(...)
#endif

signed main() {
    int N;
    in>>N;

    vector<Node> nodes(N);
    for(int n=0; n<N-1; ++n){
        int a,b,w;
        in>>a>>b>>w;
        nodes[a].neighbors.emplace_back(b, w);
        nodes[b].neighbors.emplace_back(a, w);
    }

    function<void(int,int,int)> setRoot = [&](int i, int parent, int depth){
        Node& n = nodes[i];
        n.parent = parent;
        n.children.resize(0, {0,0});
        n.depth = depth;

        for(const Edge& e : nodes[i].neighbors) {
            if (e.i != parent) {
                setRoot(e.i, i, depth+1);
                n.children.push_back(e);
            }
        }
    };
    setRoot(0,0,0);
    printTree(nodes,0,0);

    function<void(int)> populBestChi = [&](int i){
        Node& n = nodes[i];
        for (const Edge& e : nodes[i].children) {
            populBestChi(e.i);
            int d = nodes[e.i].maxDist + e.w;

            if (d > n.maxDist) {
                n.maxDist2 = n.maxDist;
                n.maxDist = d;
                n.maxChi = e.i;
            } else if (d > n.maxDist2) {
                n.maxDist2 = d;
            }
        }
    };
    populBestChi(0);

    function<void(int,int)> populateFar = [&](int i, int up){
        Node& n = nodes[i];
        n.far = max(up, n.maxDist);
        for (const Edge& e : nodes[i].children) {
            if (e.i == n.maxChi) {
                // we are going down the best children, so use the second best for "up"
                populateFar(e.i, e.w + max(up, n.maxDist2));
            } else {
                populateFar(e.i, e.w + max(up, n.maxDist));
            }
        }
    };
    populateFar(0,0);

    int root = min_element(nodes.begin(), nodes.end(), [](const Node& a, const Node& b) {
        return a.far < b.far;
    }) - nodes.begin();
    setRoot(root,root,0);
    printTree(nodes,root);

    vector<int> sortedNodes(N);
    iota(sortedNodes.begin(), sortedNodes.end(), 0);
    sort(sortedNodes.begin(), sortedNodes.end(), [&](int a, int b) {
        const Node& na = nodes[a];
        const Node& nb = nodes[b];
        return na.far > nb.far || (na.far == nb.far && na.depth > nb.depth);
    });

    auto solve = [&](int L) {
        deb("\nL =", L);
        for(Node& node : nodes){
            node.subtreeRoot = -1;
        }

        int res=0, hi=0;
        for(int lo=0; lo<N; ++lo) {
            int loi = sortedNodes[lo];
            deb("Processing", loi);

            Node& lowNode = nodes[loi];
            for(; hi < lo; ++hi) {
                int hii = sortedNodes[hi];
                deb(hii);
                if (nodes[hii].far - L <= lowNode.far) {
                    break;
                }

                int subtreeRoot = hii;
                while(nodes[subtreeRoot].subtreeRoot != -1) {
                    subtreeRoot = nodes[subtreeRoot].subtreeRoot;
                }
                int updSubtreeRoot = hii;
                while(nodes[updSubtreeRoot].subtreeRoot != -1) {
                    nodes[updSubtreeRoot].subtreeRoot = subtreeRoot;
                    updSubtreeRoot = nodes[updSubtreeRoot].subtreeRoot;
                }

                deb(hii, subtreeRoot);
                nodes[subtreeRoot].controlledNodes -= 1;
                assert(nodes[subtreeRoot].controlledNodes >= 0);
            }
            deb();

            int& controlledNodes = lowNode.controlledNodes;
            controlledNodes = 1; // itself
            for(const Edge& e : lowNode.children) {
                // children has surely been visited since it has a higher "far" value
                controlledNodes += nodes[e.i].controlledNodes;
                nodes[e.i].subtreeRoot = loi;
            }
            res = max(res, controlledNodes);
        }
        return res;
    };

    int K;
    in>>K;
    for(int k=0; k<K; ++k) {
        int L;
        in>>L;
        out<<solve(L)<<"\n";
    }
}
