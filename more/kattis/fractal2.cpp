#include <bits/stdc++.h>
using namespace std;
using ld=long double;

#ifdef DEBUG
template<class A,class B>ostream&operator<<(ostream&o,const pair<A,B>&p){cout<<"("<<p.first<<", "<<p.second<<")";return o;}
template<class T,typename=typename enable_if<!is_same<T, string>::value,decltype(*begin(declval<T>()))>::type>ostream&operator<<(ostream&o,const T&v){cout<<"[";for(auto it=v.begin();it!=v.end();++it){if(it!=v.begin()){cout<<", ";}cout<<*it;}cout<<"]";return o;}
void deb(){cout<<endl;}template<class T,class...Ts>void deb(const T&t,const Ts&...args){cout<<t;if(sizeof...(args)!=0){cout<<"  ";}deb(args...);}
#else
#define deb(...)
#endif

struct Point{
	ld x,y;
};

int main(){
	int T;
	cin>>T;
	for(int t=0;t<T;++t){
		int N;
		cin>>N;

		vector<ld> cumulativeLengths(N,0);
		vector<ld> lengths(N,0);
		vector<ld> directions(N);
		vector<Point> points(N);
		for(int n=0;n<N;++n){
			cin>>points[n].x>>points[n].y;
			if(n!=0){
				lengths[n] = hypotl(points[n].x-points[n-1].x, points[n].y-points[n-1].y);
				cumulativeLengths[n] = cumulativeLengths[n-1] + lengths[n];
				directions[n] = atan2l(points[n].y-points[n-1].y, points[n].x-points[n-1].x);
			}
		}

		Point curPoint = points[0];
		ld curLen = hypotl(points[N-1].x-points[0].x, points[N-1].y-points[0].y);
		ld curDir = atan2l(points[N-1].y-points[0].y, points[N-1].x-points[0].x);
		for_each(lengths.begin(), lengths.end(), [curLen](ld &d){ d /= curLen; });
		for_each(cumulativeLengths.begin(), cumulativeLengths.end(), [&](ld &d){ d /= cumulativeLengths[N-1]; });
		for_each(directions.begin(), directions.end(), [curDir](ld &d){ d -= curDir; });
		deb(lengths);
		deb(cumulativeLengths);
		deb(directions);

		int D;
		ld F;
		cin>>D>>F;
		for(int d=0;d<D;++d){
			int i = distance(cumulativeLengths.begin(),
				upper_bound(cumulativeLengths.begin(), cumulativeLengths.end(), F));

			// translation vector for curPoint
			ld trLen = curLen * hypotl(points[i-1].x-points[0].x, points[i-1].y-points[0].y) / hypotl(points[N-1].x-points[0].x, points[N-1].y-points[0].y);
			ld trDir = curDir + atan2l(points[i-1].y-points[0].y, points[i-1].x-points[0].x) - atan2l(points[N-1].y-points[0].y, points[N-1].x-points[0].x);
			/*cout<<F<<" -> "<<i
					 <<"\n     point: "<<curPoint.x<<" "<<curPoint.y
				    <<"\n   len&dir: "<<curLen<<" "<<curDir
					 <<"\n   tr  l&d: "<<trLen<<" "<<trDir<<"\n\n";*/
			curPoint.x += trLen * cos(trDir);
			curPoint.y += trLen * sin(trDir);

			curLen *= lengths[i];
			curDir += directions[i];
			F -= cumulativeLengths[i-1];
			F /= (cumulativeLengths[i]-cumulativeLengths[i-1]);
		}

		/*cout<<F
					<<"\n     point: "<<curPoint.x<<" "<<curPoint.y
					<<"\n   len&dir: "<<curLen<<" "<<curDir<<"\n\n";*/
		curPoint.x += F * curLen * cos(curDir);
		curPoint.y += F * curLen * sin(curDir);

		cout << setprecision(10) << curPoint.x << " " << setprecision(10) << curPoint.y << "\n";
	}
}