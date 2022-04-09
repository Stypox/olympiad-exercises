struct std::tm tmp;

ll readDate(){
	cin>>get_time(&tmp, "%Y-%m-%d %H:%M");
	return chrono::system_clock::from_time_t(mktime(&tmp)).time_since_epoch().count();
}

int main(){
	int T;
	cin>>T;
	for(int t=0;t<T;++t){
		ll N,C;
		cin>>N>>C;
		vector<pair<ll,ll>> spans;
		for(int n=0;n<N;++n){
			string s;
			cin>>s;

			ll d1=readDate();
			ll d2=readDate()+C*60*1000000000;
			spans.push_back({d1,d2});
		}

		sort(spans.begin(), spans.end());
		priority_queue<ll,vector<ll>,greater<ll>> pq{};
		size_t res=0;
		for(auto [d1,d2] : spans){
			while(!pq.empty() && pq.top()<=d1){
				pq.pop();
			}
			pq.push(d2);
			res=max(res,pq.size());
		}

		cout<<res<<"\n";
	}
}