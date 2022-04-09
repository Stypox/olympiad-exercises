#include<bits/stdc++.h>
#include <signal.h>

using namespace std;

struct SegmentTree {
    static int higherPowerOf2(int x) {
        int res = 1;
        while (res < x) res *= 2;
        return res;
    }

	vector<int> data;
	SegmentTree(int n) : data(2 * higherPowerOf2(n), 0) {}

	int query(int i, int a, int b, int x, int y) {
		if (b <= x || a >= y) return 0;
		if (b <= y && a >= x) return data[i];

		return query(i*2,   a, (a+b)/2, x, y)
		     + query(i*2+1, (a+b)/2, b, x, y);
	}

	int update(int i, int a, int b, int x, int v) {
		if (x < a || x >= b) return data[i];
		if (a == b-1) {
			assert(a == x);
			return data[i] = v;
		}

		return data[i] = update(i*2,   a, (a+b)/2, x, v)
			            + update(i*2+1, (a+b)/2, b, x, v);
	}

	int query(int x, int y) {
		assert(x <= y);
		return query(1, 0, data.size()/2, x, y);
	}

    int sumOfAll() {
        return data[1];
    }

	void update(int x, int v) {
		update(1, 0, data.size()/2, x, v);
	}
};

template<class A, class B>

class doppiamappa{
    public:
        map<A, B> uno;
        map<B, A> due;

        B atPrimo(const A& a) {
            return uno[a];
        }

        A atSecon(const B& b) {
            return due[b];
        }

        void add(const A& a, const B& b) {
            uno[a] = b;
            due[b] = a;
        }

        void removePrimo(const A& a) {
            const B& b = uno[a];
            uno.erase(a);
            due.erase(b);
        }

        void removeSecon(const B& b) {
            const A& a = due[b];
            uno.erase(a);
            due.erase(b);
        }
};

class street{
    public:
        int from, to;//nodi
        int durata;
        int nmacchine=0;
        string nome;

        doppiamappa<int, int> coda;//macchina, tempo

};

class sched {
    public:
        sched() : sched{0} {}
        sched(int N) : data{N}, st{N} {}

        vector<pair<int,int>> data;
        map<int, int> stradaToPos;
        SegmentTree st;

        pair<int,int>& atPos(int pos) {
            return data[pos];
        }

        pair<int,int>& atStrada(int strada) {
            return data[stradaToPos[strada]];
        }

        void set(int pos, int strada, int valore) {
            data[pos] = {strada, valore};
            stradaToPos[strada] = pos;
            st.update(pos, valore);
        }

        auto begin() {
            return data.begin();
        }

        auto end() {
            return data.end();
        }

        int nextGreenTime(int currTime, int strada, int macchineInCodaDavanti) {
            int result = currTime - (currTime % st.sumOfAll()) + st.query(0, stradaToPos[strada]);
            if (result < currTime) {
                result += st.sumOfAll();
            }

            auto [ignore, duration] = atStrada(strada);
            result += st.sumOfAll() * (macchineInCodaDavanti / duration);
            result += macchineInCodaDavanti % duration;

            return result;
        }
};

class node {
    public:
        vector<int> entrata;//strada in entrata
        sched schedule;
};

class car {
    public:
        vector<int> path;
        int tFine;
};

long seed;


//TODO ignorare le macchine in ritardo

int simTime, nNode, nStreet, nCars, bonus;

vector<street> strade;
vector<node> grafo;

vector<car> cars;


void read();
void init();
void propaga();
void popola();
void write(const string& name);
int score();
int optimize(int nodo);

bool run = true;
void sigint(int sig) {
    run = false;
}

int main(int argc, char *argv[]) {
    freopen("./input/a.txt", "r", stdin);
    seed = time(NULL);
    srand(seed);
    signal(SIGINT, sigint);

    read();
    init();
    propaga();
    write(to_string(seed) + "_iniziale");

    while (run) {
        // fai cose
        //break;
        return 0;
    }

    write(to_string(seed));
}

void read(){
    cin >> simTime >> nNode >> nStreet >> nCars >> bonus;

    strade.resize(nStreet);
    grafo.resize(nNode);

    map<string, int> mappaStrade;

    for(int i=0; i<nStreet; i++){
        cin>>strade[i].from>>strade[i].to>>strade[i].nome>>strade[i].durata;
        grafo[strade[i].to].entrata.push_back(strade[i].from);
        mappaStrade[strade[i].nome] = i;
    }


    cars.resize(nCars);
    for(int i=0; i<nCars; i++){
        int n;
        cin>>n;
        cars[i].path.resize(n);
        for(int j=0; j<n; j++){
            string name;
            cin>>name;
            cars[i].path[j]=mappaStrade[name];
            strade[mappaStrade[name]].nmacchine++;
        }
    }
}


void init(){
    for(int a=0; a<nNode; a++){
        for(int i=0; i<grafo[a].entrata.size(); i++){
            grafo[a].schedule.set(i, grafo[a].entrata[i], strade[grafo[a].entrata[i]].nmacchine);
        }
    }
    propaga();
}


void propaga() {
    struct dato {
        int time, car, pathPos;

        bool operator<(const dato& other) {
            return this->time > other.time;
        }
    };

    priority_queue<dato> pq;
    for (int i=0; i<cars.size(); ++i) {
        pq.push(dato{strade[cars[i].path[0]].durata, i, cars[i].path[0]});
        cars[i].tFine = simTime + bonus;
    }

    vector<int> macchineAccodate(strade.size());
    while (!pq.empty()) {
        dato d = pq.top();
        pq.pop();

        if (d.time > simTime) {
            break;
        }

        macchineAccodate[cars[d.car].path[d.pathPos]]--;
        d.pathPos++;

        if (d.pathPos == cars[d.car].path.size()) {
            cars[d.car].tFine = d.time;

        } else {
            int strada = cars[d.car].path[d.pathPos];
            sched& schedule = grafo[strade[strada].to].schedule;
            d.time = schedule.nextGreenTime(d.time, strada, macchineAccodate[strada]);
            d.time += strade[strada].durata;

            macchineAccodate[strada]++;
            pq.push(d);
        }
    }
}

void write(const string& name) {
    ofstream out{name + ".txt"};

    out << grafo.size() << endl;
    for (int i=0; i<grafo.size(); ++i){
        cout << i << endl << grafo[i].schedule.data.size() << endl;
        for (auto [strada, time] : grafo[i].schedule) {
            cout << strade[strada].nome << " " << time << endl;
        }
    }
}

void propaga(){

}

int optimize(int nodo){
    return 0;
}

int score() {
    return accumulate(cars.begin(), cars.end(), 0, [](const int& curr, const car& c) {
        return curr + bonus + (simTime - c.tFine);
    });
}

