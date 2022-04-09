//#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

vector<const char*> files{"./input/00-example.txt", "./input/01-the-cloud-abyss.txt", "./input/02-iot-island-of-terror.txt",
	"./input/03-etheryum.txt", "./input/04-the-desert-of-autonomous-machines.txt", "./input/05-androids-armageddon.txt"};

double P = 0.999;
double constace = 10000;
double A = 1;
double B = 2;

int initStam, maxStam, turns;

struct Demon {
	int indice;
	int needStam, recovTurns, givesStam;
	vector<int> frags, cumFrags;

	int frammentiRaccolti(int turnoCorrente) {
		if (cumFrags.empty()) {
			return 0;
		}

		return cumFrags[
						min((long long) cumFrags.size(),
							 (long long) (turns-turnoCorrente))
						- 1LL];
	}
};
vector<Demon> demons;

double randFloat() {
	return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

void leggiInput() {
	int D;
	cin>>initStam>>maxStam>>turns>>D;

	demons.resize(D);
	for(int dd=0;dd<D;++dd){
		Demon& d = demons[dd];
		d.indice=dd;

		int N;
		cin>>d.needStam>>d.recovTurns>>d.givesStam>>N;

		d.frags.resize(N);
		d.cumFrags.resize(N);
		if (N != 0) {
			cin>>d.frags[0];
			d.cumFrags[0]=d.frags[0];

			for(int n=1;n<N;++n){
				cin>>d.frags[n];
				d.cumFrags[n]=d.cumFrags[n-1]+d.frags[n];
			}
		}
	}
}

void scriviOutput(vector<int> sol) {
	for(int i = 0; i < sol.size(); i++) {
		cout << sol[i] << "\n";
	}
}

struct Event {
	int t;
	function<void()> f;

	Event(int tt, function<void()> ff) : t{tt}, f{ff} {};

	bool operator<(const Event& other) const {
		return t > other.t;
	}
};

pair<int, vector<int>> solve() {
	int s=initStam;
	int t=0;
	int score=0;

	priority_queue<Event> events;
	vector<int> sol;
	unordered_set<int> demoniDaFare;
	for(int d=0;d<demons.size();++d){
		demoniDaFare.insert(d);
	}

	while(t<turns) {
		while (!events.empty() && events.top().t <= t) {
			events.top().f();
			events.pop();
		}

		int bestDemon = -1;
		float bestScore = -1;

		for(int d:demoniDaFare){
			if(demons[d].needStam <= s){
				float curScore = (randFloat() * 0.3 + 0.8)
					* pow(demons[d].frammentiRaccolti(t), A)
					/ pow((float)demons[d].needStam, B);

				if (curScore > bestScore) {
					bestScore = curScore;
					bestDemon = d;
				}
			}
		}

		if (bestDemon != -1) {
			s -= demons[bestDemon].needStam;
			score += demons[bestDemon].frammentiRaccolti(t);
			sol.push_back(demons[bestDemon].indice);

			events.push(Event(t+demons[bestDemon].recovTurns, [bestDemon,&s]() { s = min(maxStam, s + demons[bestDemon].givesStam); }));
			demoniDaFare.erase(bestDemon);
		}
		t++;
	}

	return {score, sol};
}


bool run = true;
void sigint(int sig) {
   run = false;
}

int main(int argc, const char* argv[]) {
	freopen(files[argv[1][0]-'0'], "r", stdin);
	freopen(argv[1], "w", stdout);
   signal(SIGINT, sigint);
	leggiInput();

	int seme = 1646939364;
	srand(1646939364);

	int bestissimo = 0;
	vector<int> finalSol;

	int bestScore = 0;
	double T = 0.0f;
	while(run) {
		auto origDemons = demons;
		auto origP = P;
		auto origConstace = constace;
		auto origA = A;
		auto origB = B;

		for (int i=0; i<min(max(1., T/100), demons.size()+.0); ++i) {
			int a = rand() % demons.size();
			int b = rand() % demons.size();
			swap(demons[a], demons[b]);
		}
		//P *= pow(1.001, T / 100000 * randFloat() - 0.5);
		//constace *= pow(1.001, T / 100000 * randFloat() - 0.5);
		A *= pow(1.001, T / 100000 * (randFloat() - 0.5));
		B *= pow(1.02, T / 100000 * (randFloat() - 0.5));

		auto[score, sol] = solve();
		if (score > bestissimo) {
			bestissimo = score;
			finalSol = sol;
		}
		if (T == 0.0f) {
			T = score * 10;
		}

		double coeff = pow(M_E, (score - bestScore) / T);
		if (score >= bestScore || randFloat() < coeff) {
			bestScore = score;
		} else {
			demons = origDemons;
			P = origP;
			constace = origConstace;
			A = origA;
			B = origB;
		}

		T *= 0.95;
		cerr<<setw(15)<<T<<"° "<<setw(10)<<score<<" "<<setw(10)<<bestissimo<<"\n";
	}

	scriviOutput(finalSol);
	cerr<<seme<<"\n";
}
