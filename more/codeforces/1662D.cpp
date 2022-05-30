#include <bits/stdc++.h>
using namespace std;

string clean(const string& s) {
	string r;
	int bCount=0;
	for(char c:s) {
		if (c=='B') ++bCount;
		else r.push_back(c);
	}

	while(true){
		bool done=true;
		for(int i=0;i<(int)r.size()-1;++i){
			if(r[i]==r[i+1]) {
				r = r.substr(0,i) + r.substr(i+2);
				done=false;
				break;
			}
		}
		if(done) break;
	}

	if (bCount%2) r+="B";
	return r;
}

int main() {
	int T;
	cin>>T;
	while(T--) {
		string s1, s2;
		cin>>s1>>s2;
		cout<<(clean(s1) == clean(s2) ? "YES" : "NO")<<endl;
	}
}