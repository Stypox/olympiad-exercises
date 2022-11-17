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
#define cout Do not use cout!!!
#define cin Do not use cin!!!

struct Node{
	vector<int> to;
	int t=0;
	int ways=0;
};

signed main() {
	int N,M,S,T;
	in>>N>>M>>S>>T;

	vector<Node> nodes(N);
	for(int m=0;m<M;++m){
		int a,b;
		in>>a>>b;
		nodes[a].to.push_back(b);
	}

	queue<tuple<int,int,int>> q;
	q.push({S,1,S});
	nodes[S].ways=1;
	while(!q.empty()) {
		auto[i,t,p]=q.front();
		q.pop();

		if(nodes[i].t == 0){
			nodes[i].t = t;
			nodes[i].ways = nodes[p].ways;
			for(auto&& e:nodes[i].to){
				q.push({e,t+1,i});
			}
		} else if (nodes[i].t == t) {
			nodes[i].ways += nodes[p].ways;
		}
	}

	out<<nodes[T].t-1<<" "<<nodes[T].ways<<"\n";
}
