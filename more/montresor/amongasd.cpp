#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
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
#define cout Do not use cout!!!
#define cin Do not use cin!!!


enum class Visitor { both, imposter, student, none };

struct Edge {
    int to;
    int min, max;
    int chosen;
    int index;

    Edge(int to, int min, int max, int index) : to(to), min(min), max(max), chosen(min), index(index) {}
    Edge(int to, int time) : Edge(to, time, time, -1) {}
    Edge() : Edge(0, 0, 0, -1) {}

    int getSetAppropiateTime(Visitor visitor) {
        switch (visitor) {
            case Visitor::imposter: {
                chosen = min;
                break;
            }
            case Visitor::student:
            case Visitor::both: {
                chosen = max;
                break;
            }
            case Visitor::none:
            default: {
                throw "Unreachable";
            }
        }

        return chosen;
    }
};


struct Node {
    vector<Edge> adjList;
    Node *parent_I = nullptr, *parent_S = nullptr;
    int hops = 0, distance = 0;
    Visitor visitedBy = Visitor::none;

    Node() {}
    void setParentIfNull(Node& parent) { // FIXME: si rischia di assegnare un parent a I e S... è un problema?
        if ((parent.visitedBy == Visitor::student || parent.visitedBy == Visitor::both) && parent_I == nullptr) parent_I = &parent;
        if ((parent.visitedBy == Visitor::imposter || parent.visitedBy == Visitor::both) && parent_S == nullptr) parent_S = &parent;
    }
    void setParent(Node& parent) { // FIXME: si rischia di assegnare un parent a I e S... è un problema?
        if (parent.visitedBy == Visitor::student || parent.visitedBy == Visitor::both) parent_I = &parent;
        if (parent.visitedBy == Visitor::imposter || parent.visitedBy == Visitor::both) parent_S = &parent;
    }
    void mergeVisitors(Visitor visitor) {
        if (visitor == visitedBy) return;
        visitedBy = Visitor::both; // check della correttezza
    }
};

ostream& operator<< (ostream& out, const Node& node) {
    return out << node.distance << ' ' << (int) node.visitedBy;
}


void ventilate (vector<Node>& nodes, int I, int S, int F);

int main () {
    int N, M, K, I, S, F;
    in >> N >> M >> K >> I >> S >> F;

    vector<Node> nodes(N);
    for (int i = 0; i < M; ++i) {
        int u, v, t;
        in >> u >> v >> t;
        nodes[u].adjList.push_back(Edge(v, t));
    }
    for (int i = 0; i < K; ++i) {
        int u, v, min, max;
        in >> u >> v >> min >> max;
        nodes[u].adjList.push_back(Edge(v, min, max, i));
    }

    ventilate(nodes, I, S, F);
    nodes[I].parent_I = nodes[I].parent_S = nodes[S].parent_I = nodes[S].parent_S = nullptr;

    deb(nodes);
    out << (int) nodes[F].visitedBy << endl;

    out << 378426374 << endl;

    vector<int> chosenEdgeValues(K);
    for (auto&& node : nodes) {
        for (auto&& edge : node.adjList) {
            if (edge.index != -1) {
                chosenEdgeValues[edge.index] = edge.chosen;
            }
        }
    }
    for (int i = 0; i < K; ++i) {
        if (i != 0) {
            out << " ";
        }
        out << chosenEdgeValues[i];
    }
    out << endl;

    return 0;
}


struct QueueEntity {
    int distance, node;
    QueueEntity(int distance, int node) : distance(distance), node(node) {}
    QueueEntity() : QueueEntity(0, 0) {}

    bool operator< (const QueueEntity& other) const {
        // le priority queue vanno al contrario, quindi > invece che < per ordinare al minimo
        return distance > other.distance;
    }
};

void ventilate(vector<Node>& nodes, int I, int S, int F) {
    vector<bool> elaborated(nodes.size(), false);

    priority_queue<QueueEntity> queue;
    queue.push(QueueEntity(0, I));
    queue.push(QueueEntity(0, S));
    nodes[I].visitedBy = Visitor::imposter;
    nodes[S].visitedBy = Visitor::student;

    while (!queue.empty()) {
        int node = queue.top().node;
        queue.pop();
        if (elaborated[node]) continue;
        if (node == F) break;
        elaborated[node] = true;

        for (Edge& edge : nodes[node].adjList) {
            Node& target = nodes[edge.to];
            if (target.visitedBy == Visitor::none) {
                target.visitedBy = nodes[node].visitedBy;
                target.distance = nodes[node].distance + edge.getSetAppropiateTime(nodes[node].visitedBy);
                target.hops = nodes[node].hops + 1; // TODO: solo se imposter
                target.setParent(nodes[node]);
                queue.push(QueueEntity(target.distance, edge.to));
            } else if (target.distance < nodes[node].distance + edge.getSetAppropiateTime(nodes[node].visitedBy)) {
                target.setParentIfNull(nodes[node]);
            } else if (target.distance == nodes[node].distance + edge.getSetAppropiateTime(nodes[node].visitedBy)) {
                target.setParentIfNull(nodes[node]); // TODO: update hops se necessario
                target.mergeVisitors(nodes[node].visitedBy);
            } else if (target.distance > nodes[node].distance + edge.getSetAppropiateTime(nodes[node].visitedBy)) {
                target.visitedBy = nodes[node].visitedBy;
                target.distance = nodes[node].distance + edge.getSetAppropiateTime(nodes[node].visitedBy);
                target.hops = nodes[node].hops + 1; // TODO: solo se imposter
                target.setParent(nodes[node]);
                queue.push(QueueEntity(target.distance, edge.to));
            }
        }
    }
}
