#include <bits/stdc++.h>
using namespace std;

int main(){
	char s;
	cin>>s;
	int alwaysup=0, alwaysdown=0, asyouwant=0;
	bool firstStep=true;
	while(1){
		char c;
		cin>>c;
		if(cin.eof() || (c!='U' && c!='D')) break;
		if(firstStep){
			if(c=='U' && s=='U'){
				++alwaysdown;
			} else if (c=='U' && s=='D') {
				alwaysdown+=2;
				alwaysup+=1;
			} else if (c=='D' && s=='U'){
				alwaysdown+=1;
				alwaysup+=2;
			} else if (c=='D' && s=='D'){
				++alwaysup;
			}
		} else if(c=='U'){
			alwaysdown+=2;
		} else {
			alwaysup+=2;
		}
		if (c!=s){
			++asyouwant;
		}
		firstStep=false;
		s=c;
	}
	cout<<alwaysup<<"\n"<<alwaysdown<<"\n"<<asyouwant<<"\n";
}