#include <bits/stdc++.h>
using namespace std;

int main(){
	while(1){
		int N;
		cin>>N;
		if (N==0) break;
		cin.ignore();

		map<string, int> files;
		map<char, map<string, int>> hashes;
		for(int n=0;n<N;++n){
			string s;
			getline(cin, s);
			files[s]++;

			char v=0;
			for(auto c:s){
				v^=c;
			}
			hashes[v][s]++;
		}

		int collisions = 0;
		for(auto [c, coll] : hashes) {
			int countSum = 0;
			for(auto [s, count] : coll) {
				countSum += count;
			}

			for(auto [s, count] : coll) {
				collisions += (countSum - count) * count;
			}
		}

		cout<<files.size()<<" "<<collisions/2<<"\n";
	}
}
