//#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

vector<const char*> files{"./input/00-example.txt", "./input/01-the-cloud-abyss.txt", "./input/02-iot-island-of-terror.txt",
	"./input/03-etheryum.txt", "./input/04-the-desert-of-autonomous-machines.txt", "./input/05-androids-armageddon.txt"};

constexpr float P = 0.7;
constexpr double constace = 30000;

float precScore=0.0;

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
				float curScore = demons[d].frammentiRaccolti(t)
				                 * pow(P, demons[d].recovTurns)
									  * pow(10, (demons[d].givesStam - demons[d].needStam) / constace);

				if (curScore > bestScore) {
					bestScore = curScore;
					bestDemon = d;
				}
			}
		}

		if (bestDemon != -1 && bestScore >= 0) {
			precScore = bestScore;
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

int main(int argc, const char* argv[]) {
	freopen(files[argv[1][0]-'0'], "r", stdin);
	freopen(argv[1], "w", stdout);
	leggiInput();
	auto[score, sol] = solve();
	scriviOutput(sol);
	cerr<<score<<"\n";
}
