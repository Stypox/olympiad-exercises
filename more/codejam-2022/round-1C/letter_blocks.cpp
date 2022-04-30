#include<bits/stdc++.h>
using namespace std;

struct Block {
	string s;
	string actual;
	bool taken = false;

	void compute() {
		if (s.length() > 2) {
			actual = {s[0], s.end()[-1]};
		} else {
			actual = s;
		}

		if (actual.length() == 2 && actual[0] == actual[1]) {
			actual = string{s[0]};
		}
	}
};

void impossible(int t) {
	cout << "Case #" << t+1 << ": IMPOSSIBLE\n";
}

signed main() {
	int T;
	cin>>T;

	for(int t=0;t<T;++t){
		int N;
		cin>>N;
		vector<Block> blocks(N);
		for(int n=0;n<N;++n){
			cin>>blocks[n].s;
		}

		bitset<26> presentBeg{0}, presentEnd{0};
		vector<Block> nonSingletons;
		array<vector<Block>, 26> singletonsByLetter;

		for(int n=0;n<N;++n){
			blocks[n].compute();
			if (blocks[n].actual.size() == 1) {
				singletonsByLetter[blocks[n].actual[0] - 'A'].push_back(blocks[n]);
			} else {
				if (presentBeg[blocks[n].actual[0] - 'A'] || presentEnd[blocks[n].actual[1] - 'A']) {
					//cout << "h3\n";
					impossible(t);
					goto imp;
				}

				presentBeg[blocks[n].actual[0] - 'A'] = true;
				presentEnd[blocks[n].actual[1] - 'A'] = true;
				nonSingletons.push_back(blocks[n]);
			}
		}

		goto proceed;
		imp:
		continue;
		proceed:

		vector<char> startingLetters;
		for(char i=0;i<26;++i){
			if (presentBeg[i] && !presentEnd[i]) {
				startingLetters.push_back('A' + i);
			}
		}

		string result;
		for(auto currLetter : startingLetters) {
			for(int i=0;i<nonSingletons.size()+1;++i){
				for(auto& block:singletonsByLetter[currLetter-'A']) {
					assert(!block.taken);
					block.taken = true;
					result += block.s;
				}

				bool somethingTaken = false;
				for(auto& block:nonSingletons){
					if (block.actual[0] == currLetter) {
						assert(!block.taken);
						block.taken = true;
						result += block.s;
						currLetter = block.actual[1];
						somethingTaken=true;
						break;
					}
				}

				if (!somethingTaken) {
					break;
				}
			}
		}

		for(char i=0;i<26;++i){
			for(auto& block:singletonsByLetter[i]) {
				if(!block.taken) {
					result += block.s;
				}
			}
		}

		for(auto& block:nonSingletons) {
			if (!block.taken) {
				//cout << "h4\n";
				impossible(t);
				goto imp;
			}
		}

		char prev='\0';
		bitset<26> seen{0};
		for(char c:result){
			if (c!=prev){
				if(seen[c-'A']) {
					impossible(t);
					goto imp;
				} else {
					seen[c-'A'] = true;
				}
				prev = c;
			}
		}

		cout << "Case #" << t+1 << ": " << result << "\n";
	}
}