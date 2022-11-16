#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

ifstream in{"input.txt"};
ofstream out{"output.txt"};
#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<"\n";}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

struct Node{
	vector<int> to;
	bitset<420> visited;
};

signed main() {
	constexpr int LCM = 420; // LCM of 1,2,3,4,5,6,7
	int N,M,K;
	in>>N>>M>>K;

	vector<Node> nodes(N);
	for(int m=0;m<M;++m){
		int a,b;
		in>>a>>b;
		nodes[a].to.push_back(b);
		nodes[b].to.push_back(a);
	}

	for(int k=0;k<K;++k){
		int L;
		in>>L;
		for(int l=0;l<L;++l){
			int h;
			in>>h;
			for(int i=l;i<LCM;i+=L){
				nodes[h].visited[i]=true;
			}
		}
	}

	int res=-1;
	queue<pair<int,int>> q;
	q.push({0, 0});
	while(!q.empty()) {
		auto [n,t] = q.front();
		q.pop();

		if (nodes[n].visited[t%LCM]) {
			continue;
		}
		nodes[n].visited[t%LCM] = true;

		if (n == N-1) {
			res=t;
			break;
		}

		q.push({n,t+1}); // either wait 1 tick here
		for(auto&& e:nodes[n].to) {
			q.push({e,t+1}); // or go to another node
		}
	}

	out<<res<<"\n";
}
