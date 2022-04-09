#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

vector<const char*> files{"./input/00-example.txt", "./input/01-the-cloud-abyss.txt", "./input/02-iot-island-of-terror.txt",
	"./input/03-etheryum.txt", "./input/04-the-desert-of-autonomous-machines.txt", "./input/05-androids-armageddon.txt"};

struct Demon {
	int needStam, recovTurns, givesStam;
	vector<int> frags, cumFrags;
};

int initStam, maxStam, turns;
vector<Demon> demons;

void leggiInput() {
	int D;
	cin>>initStam>>maxStam>>turns>>D;

	demons.resize(D);
	for(auto&& d:demons){
		int N;
		cin>>d.needStam>>d.recovTurns>>d.givesStam>>N;

		d.frags.resize(N);
		cin>>d.frags[0];
		d.cumFrags[0]=d.frags[0];

		for(int n=1;n<N;++n){
			cin>>d.frags[n];
			d.cumFrags[n]=d.cumFrags[n-1]+d.frags[n];
		}
	}
}

int main(int argc, const char* argv[]) {
	freopen(files[argv[1][0]-'0'], "r", stdin);
	freopen(argv[1], "w", stdout);
	leggiInput();
}
