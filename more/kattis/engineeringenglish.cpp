#include <bits/stdc++.h>
using namespace std;

int main(){
	unordered_set<string> seenwords;
	while(1){
		string original, lowercase, separator;
		while(1){
			char ch = cin.get();
			if (cin.eof()) break;
			if (ch==' ' || ch=='\n') {
				separator.push_back(ch);
				break;
			}
			original.push_back(ch);
			lowercase.push_back(tolower(ch));
		}
		if(original.empty()) break;

		if (seenwords.count(lowercase)) {
			cout<<'.'<<separator;
		} else {
			seenwords.insert(lowercase);
			cout<<original<<separator;
		}
	}
}