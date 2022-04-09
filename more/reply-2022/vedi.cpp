#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

vector<const char*> files{"./input/00-example.txt", "./input/01-the-cloud-abyss.txt", "./input/02-iot-island-of-terror.txt",
	"./input/03-etheryum.txt", "./input/04-the-desert-of-autonomous-machines.txt", "./input/05-androids-armageddon.txt"};

struct Demon {
	int indice;
	int needStam, recovTurns, givesStam;
	vector<int> frags, cumFrags;
};

int initStam, maxStam, turns;
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

int main(int argc, const char* argv[]) {
	freopen(files[argv[1][0]-'0'], "r", stdin);
	leggiInput();

	int maxneedStam=-1, maxrecovTurns=-1, maxgivesStam=-1, maxcumFrags=-1, sumcumFrags=0;
	for (auto&& d : demons) {
		maxneedStam = max(d.needStam, maxneedStam);
		maxrecovTurns = max(d.recovTurns, maxrecovTurns);
		maxgivesStam = max(d.givesStam, maxgivesStam);
		maxcumFrags = max(d.cumFrags.empty() ? 0 : d.cumFrags.back(), maxcumFrags);
		sumcumFrags += d.cumFrags.empty() ? 0 : d.cumFrags.back();
	}

	cout<<setw(10)<<maxneedStam<<" "<<setw(10)<<maxrecovTurns<<" "<<setw(10)<<maxgivesStam<<" "<<setw(10)<<maxcumFrags<<" "<<setw(10)<<sumcumFrags<<" "<<setw(10)<<sumcumFrags/(float)demons.size()<<"\n";
}
