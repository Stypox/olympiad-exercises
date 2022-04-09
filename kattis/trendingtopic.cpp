#include <bits/stdc++.h>
using namespace std;

int main(){
	array<map<string, int>, 7> days;
	map<string, int> allDays;
	map<int, set<string>> allDaysReverse;
	auto eraseFromAllDaysReverse = [&](int frequency, const string& value){
		allDaysReverse[frequency].erase(value);
		if(allDaysReverse[frequency].empty()){
			allDaysReverse.erase(frequency);
		}
	};

	while(1){
		string s;
		cin>>s;
		if(cin.eof() || s.empty()) break;

		if(s=="<text>"){
			for(int i=5;i>=0;--i){
				swap(days[i], days[i+1]);
			}

			for(auto&& [v, f] : days[0]){
				int& allDaysFrequency=allDays[v];
				eraseFromAllDaysReverse(allDaysFrequency, v);
				allDaysFrequency-=f;
				if(allDaysFrequency==0) {
					allDays.erase(v);
				} else {
					allDaysReverse[allDaysFrequency].insert(v);
				}
			}
			days[0].clear();

			while(1){
				cin>>s;
				if (s=="</text>") break;
				if (s.length()<4) continue;
				days[0][s]++;
			}

			for(auto&& [v, f] : days[0]){
				int& allDaysFrequency=allDays[v];
				eraseFromAllDaysReverse(allDaysFrequency, v);
				allDaysFrequency+=f;
				allDaysReverse[allDaysFrequency].insert(v);
			}

		} else {
			assert(s=="<top");
			int N;
			cin>>N;
			cin>>s;
			cout<<"<top "<<N<<">\n";

			auto it=allDaysReverse.rbegin();
			int printedWords=0;
			while(it!=allDaysReverse.rend()&&printedWords<N){
				printedWords+=it->second.size();
				for(auto&& s:it->second){
					cout<<s<<" "<<it->first<<"\n";
				}
				it++;
			}
			cout<<"</top>\n";
		}
	}
}