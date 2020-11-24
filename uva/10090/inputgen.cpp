#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

ofstream o{"input.txt"};

int main(int argc, char const* argv[]) {
	srand(atoi(argv[1]));
	for(int n=0;n<1000;++n){
		int N=5+rand()%100;
		int n1=1+rand()%(N-1), n2=1+rand()%(N-1);
		int c1=rand()%100, c2=rand()%100;
		o<<N<<"\n"<<c1<<" "<<n1<<"\n"<<c2<<" "<<n2<<"\n";
	}
	o<<"0\n";
}
