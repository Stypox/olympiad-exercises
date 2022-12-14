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
    int distance = 0;
    Visitor visitedBy = Visitor::none;
    int parent;

    Node() {}
    void mergeVisitors(Visitor visitor) {
        if (visitor == visitedBy) return;
        visitedBy = Visitor::both; // check della correttezza
    }
};

ostream& operator<< (ostream& out, const Node& node) {
    return out << node.distance << ' ' << (int) node.visitedBy;
}

void resetDistance(vector<Node>& nodes, int I, int S) {
    for (auto&& node : nodes) {
        node.distance = numeric_limits<int>::max();
    }
    nodes[I].distance = 0;
    nodes[S].distance = 0;
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
    resetDistance(nodes, I, S);

    priority_queue<QueueEntity> queue;
    queue.push(QueueEntity(0, I));
    queue.push(QueueEntity(0, S));
    nodes[I].visitedBy = Visitor::imposter;
    nodes[S].visitedBy = Visitor::student;

    while (!queue.empty()) {
        int nodeIndex = queue.top().node;
        int visitDistance = queue.top().distance;
        queue.pop();
        if (nodeIndex == F) break;

        Node& node = nodes[nodeIndex];
        if (visitDistance > node.distance) continue;

        for (Edge& edge : node.adjList) {
            Node& target = nodes[edge.to];
            int newDistance = node.distance + edge.getSetAppropiateTime(node.visitedBy);
            if (newDistance < target.distance) {
                // this branch is taken also when target.visitedBy==none,
                // since target.distance would be infinite
                target.visitedBy = node.visitedBy;
                target.distance = newDistance;
                queue.push(QueueEntity(newDistance, edge.to));
            } else if (target.distance == newDistance) {
                // will be visited later, so need to merge visitors
                target.mergeVisitors(node.visitedBy);
            }
        }
    }
}

void dijkstraOnChosenEdges(vector<Node>& nodes, int A, int B) {
    resetDistance(nodes, A, A);

    priority_queue<QueueEntity> queue;
    queue.push(QueueEntity(0, A));

    while (!queue.empty()) {
        int nodeIndex = queue.top().node;
        int visitDistance = queue.top().distance;
        queue.pop();
        if (nodeIndex == B) break;

        Node& node = nodes[nodeIndex];
        if (visitDistance > node.distance) continue;

        for (Edge& edge : node.adjList) {
            Node& target = nodes[edge.to];
            int newDistance = node.distance + edge.chosen;
            if (newDistance < target.distance) {
                target.parent = nodeIndex;
                target.distance = newDistance;
                queue.push(QueueEntity(newDistance, edge.to));
            }
        }
    }
}


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

    // --- print whether the F node is first reached by imposter or students
    out << (int) nodes[F].visitedBy << endl;

    // --- print the lengths of the paths for imposter and students
    dijkstraOnChosenEdges(nodes, S, F);
    int studentsPathLength = nodes[F].distance;
    dijkstraOnChosenEdges(nodes, I, F);
    out << nodes[F].distance << " " << studentsPathLength << endl;

    // --- print the values chosen for the K edges
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

    // --- print the rooms visited by the imposter
    vector<int> imposterRooms{F};
    while (imposterRooms.back() != I) {
        imposterRooms.push_back(nodes[imposterRooms.back()].parent);
    }
    int R = imposterRooms.size();
    out << R << endl;
    for (int i = 0; i < R; ++i) {
        if (i != 0) {
            out << " ";
        }
        out << imposterRooms[R-i-1];
    }
}
