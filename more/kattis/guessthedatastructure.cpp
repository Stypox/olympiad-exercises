#include <bits/stdc++.h>
using namespace std;

int main(){
	while(1) {
		int N=-1;
		cin>>N;
		if (cin.eof()) break;

		stack<int> s;
		queue<int> q;
		priority_queue<int> pq;
		bool vs=true, vq=true, vpq=true;

		int count=0;
		for(int n=0;n<N;++n){
			int i,x;
			cin>>i>>x;

			if (i == 1) {
				count++;
				s.push(x);
				q.push(x);
				pq.push(x);
			} else {
				if (count > 0) {
					vs &= (s.top() == x);
					vq &= (q.front() == x);
					vpq &= (pq.top() == x);
					s.pop();
					q.pop();
					pq.pop();
				} else {
					vs = vq = vpq = false;
				}
				count--;
			}
		}

		if (!vs && !vq && !vpq) {
			cout<<"impossible\n";
		} else if (vs+vq+vpq > 1) {
			cout<<"not sure\n";
		} else if (vs) {
			cout<<"stack\n";
		} else if (vq) {
			cout<<"queue\n";
		} else if (vpq) {
			cout<<"priority queue\n";
		}
	}
}