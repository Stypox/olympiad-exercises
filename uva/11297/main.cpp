#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define float long double

#ifdef ONLINE_JUDGE
istream& in = std::cin;
ostream& out = std::cout;
template<class... Ts> constexpr void deb(const Ts&...) {}
template<class T, class P=string, class S=string> constexpr void debc(const T&, P="", S="") {}
#else
ifstream in{"input.txt"};
ofstream out{"output.txt"};
void deb() {cout<<"\n";} template<class T, class... Ts> void deb(T t, Ts... args) {cout<<t<<" ";deb(args...);}
template<class T, class P=string, class S=string> void debc(const T& t, P pre="", S sep=" ") {cout<<pre;for(auto&& e:t)cout<<e<<sep;cout<<"\n";}
#endif

int upperPowerOf2(int n){
	int i=0;
	while (n!=0){
		n>>=1;
		++i;
	}
	return 1<<i;
}

template<bool useMax>
constexpr int neutralValue = useMax ? -1 : numeric_limits<int>::max();

template<bool useMax>
struct SegmentTree2D {
	int N;
	vector<vector<int>> data;

	SegmentTree2D(int n) : N{upperPowerOf2(n)},
		data(N*2, vector<int>(N*2, neutralValue<useMax>)) {}

	int& at(int x, int y) {
		return data[N + x][N + y];
	}

	//       (c,d))
	// [(a,b)       -> initial query range
	//
	//       (z,w))
	// [(x,y)       -> current tree range
	//
	// 3 4
	// 1 2          -> quad order
	int getBest(int a, int b, int c, int d,
	            int x, int y, int z, int w,
				int i, int j) {

		if (x >= c || y >= d || z <= a || w <= b) {
			return neutralValue<useMax>;
		} else if (x >= a && y >= b && z <= c && w <= d) {
			return data[i][j];
		}

		int q1 = getBest(a, b, c, d, x, y, (x+z)/2, (y+w)/2, i*2,   j*2);
		int q2 = getBest(a, b, c, d, (x+z)/2, y, z, (y+w)/2, i*2+1, j*2);
		int q3 = getBest(a, b, c, d, x, (y+w)/2, (x+z)/2, w, i*2,   j*2+1);
		int q4 = getBest(a, b, c, d, (x+z)/2, (y+w)/2, z, w, i*2+1, j*2+1);

		return useMax ? max({q1, q2, q3, q4}) : min({q1, q2, q3, q4});
	}

	int getBest(int a, int b, int c, int d) {
		return getBest(a, b, c, d, 0, 0, N, N, 1, 1);
	}

	int update(int a, int b, int value,
	           int x, int y, int z, int w,
			   int i, int j) {

		if (a == x && b == y && (z-x) == 1 && (w-y) == 1) {
			deb("set",a,b,value);
			data[i][j] = value;
		} else if (a >= x && b >= y && a < z && b < w) {
			int q1 = update(a, b, value, x, y, (x+z)/2, (y+w)/2, i*2,   j*2);
			int q2 = update(a, b, value, (x+z)/2, y, z, (y+w)/2, i*2+1, j*2);
			int q3 = update(a, b, value, x, (y+w)/2, (x+z)/2, w, i*2,   j*2+1);
			int q4 = update(a, b, value, (x+z)/2, (y+w)/2, z, w, i*2+1, j*2+1);

			data[i][j] = useMax ? max({q1, q2, q3, q4}) : min({q1, q2, q3, q4});
		}
		
		return data[i][j];
	}

	void update(int a, int b, int value) {
		deb(a,b,value);
		update(a, b, value, 0, 0, N, N, 1, 1);
	}
};

int32_t main() {
	int N;
	in>>N;

	SegmentTree2D<false> stMin(N);
	SegmentTree2D<true> stMax(N);
	
	for (int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			int value;
			in>>value;
			stMax.update(i, j, value);
			stMin.update(i, j, value);
		}
	}

	int Q;
	in>>Q;
	for (int q=0;q<Q;++q){
		char type;
		in.ignore();
		in>>type;

		if (type=='q'){
			int a,b,c,d;
			in>>a>>b>>c>>d;
			--a;--b;
			deb(a,b,c,d);
			out<<stMax.getBest(a,b,c,d)<<" "<<stMin.getBest(a,b,c,d)<<"\n";

		} else if (type=='c') {
			int a,b,value;
			in>>a>>b>>value;
			--a;--b;
			stMin.update(a, b, value);
			stMax.update(a, b, value);

		} else {
			--q;
		}
	}
}
