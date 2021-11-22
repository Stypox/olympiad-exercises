#include <bits/stdc++.h>
using namespace std;

int main(){
	map<string, int> variables;
	while (1) {
		string s;
		cin>>s;
		if (cin.eof() || s.empty()) break;

		if (s == "def") {
			string name;
			int value;
			cin>>name>>value;
			variables[name]=value;

		} else if (s == "clear") {
			variables.clear();

		} else {
			assert(s == "calc");

			int res=0;
			bool unknown = false;

			string op="+";
			while (op != "=") {
				string name,newop;
				cin>>name>>newop;
				if (variables.count(name)) {
					if (op=="+"){
						res+=variables[name];
					} else {
						assert(op=="-");
						res-=variables[name];
					}
				} else {
					unknown = true;
				}

				cout<<name<<" "<<newop<<" ";
				op=newop;
			}

			if (!unknown) {
				unknown = true;
				for (auto [name, value] : variables) {
					if (value == res) {
						cout<<name<<"\n";
						unknown = false;
					}
				}
			}

			if (unknown) {
				cout<<"unknown\n";
			}
		}
	}
}