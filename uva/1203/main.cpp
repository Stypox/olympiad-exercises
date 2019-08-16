#include <bits/stdc++.h>
using namespace std;

using si = long long;
using ui = unsigned long long;
using flt = long double;
using ch = char;
using str = string;
template<class T>
using vec = vector<T>;

#ifdef ONLINE_JUDGE
istream& in = std::cin;
ostream& out = std::cout;
template<class... Ts> constexpr void deb(const Ts&...) {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
#endif

struct ii {
	si id,p,next;
	ii(si _id,si _p) : id{_id}, p{_p}, next{_p} {}
};

int main() {
	auto grt = [](const ii& a, const ii& b){ return a.next > b.next; };
	priority_queue<ii,vec<ii>,decltype(grt)> pq{grt};

	while(1){
		str ign;
		in>>ign;
		if(ign[0]=='#')break;
		si id,p;
		in>>id>>p;
		pq.push(ii{id,p});
	}

	si N;
	in>>N;
	si n = 0;
	for(;;) {
		vec<ii> old;
		old.push_back(pq.top());
		pq.pop();
		while(!pq.empty() && pq.top().next==old[0].next){
			old.push_back(pq.top());
			pq.pop();
		}
		
		sort(old.begin(),old.end(),[](const ii& a, const ii& b) { return a.id<b.id;});
		for(auto&& e : old) {
			if(n==N) break;
			out<<e.id<<"\n";
			++n;
			
			e.next+=e.p;
			pq.push(e);
		}
		if(n==N) break;
	}
}
