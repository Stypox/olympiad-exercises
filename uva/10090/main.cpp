#pragma GCC optimize ("O3")
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

pair<int,int> gcd(int a, int b, int n, int c1, int c2) {
	bool swapped = b>a;
	if (swapped) {
		// a deve essere maggiore di b
		deb("swapped");
		swap(a,b);
		swap(c1,c2);
	}

	// r -> resti, q -> quozienti
	vector<int> r{a,b}, q;
	while(r.back()!=0) {
		// algoritmo di Euclide
		q.push_back(r.end()[-2] / r.end()[-1]);
		r.push_back(r.end()[-2] % r.end()[-1]);
	}
	debc(r, "r = ");
	debc(q, "q = ");

	// il penultimo dei resti e' il gcd
	if (n % r.end()[-2] != 0) {
		deb("Impossibile!");
		return {-1,-1};
	}

	// risali ai coefficienti x e y
	int x=0,y=1;
	int qi=-2; // indice dentro q
	while(-qi<=q.size()){
		int nx = y;
		int ny = x - y*q.end()[qi];
		x=nx;
		y=ny;
		--qi;
	}
	// adesso x e y sono i due coefficienti tali che x*a+y*b=gcd(a,b)
	deb("x,y orig", x,y);
	// qui termina l'algoritmo esteso di Euclide

	// da x*a+y*b=gcd(a,b) risali a x*a+y*b=n
	int m=n/r.end()[-2]; // n=gcd*m
	x*=m;
	y*=m;
	deb("* n / gcd",x,y);

	// sommando k*dx a x e sottraendo k*dy a y (o sottraendo e sommando)
	// si ottengono coppie (x,y) che soddisfano x*a+y*b=n
	int dx=b/r.end()[-2], dy=a/r.end()[-2];
	deb("d",dx,dy);

	if (x > 0) {
		int k = x / dx;
		x -= k*dx;
		y += k*dy;
		deb(">0", k);
	} else if (x < 0) {
		int k = (-x) / dx;
		if (dx*k != -x) { // uguale a -x%dx != 0
			++k;
		}

		x += k*dx;
		y -= k*dy;
		deb("<0", k);
	}
	int smallx=x, smally=y;
	deb("optimize for smallest x",x,y);

	if (y > 0) {
		int k = y / dy;
		x += k*dx;
		y -= k*dy;
		deb(">0", k);
	} else if (y < 0) {
		int k = (-y) / dy;
		if (dy*k != -y) { // uguale a -y%dy != 0
			++k;
		}

		x -= k*dx;
		y += k*dy;
		deb("<0", k);
	}
	deb("optimize for smallest y",x,y);

	if (swapped) {
		swap(smallx, smally);
		swap(x,y);
		swap(c1,c2);
	}
	if (smallx < 0 || smally < 0) {
		return {x,y};
	} else if (x < 0 || y < 0) {
		return {smallx, smally};
	} else if (smallx*c1+smally*c2 > x*c1+y*c2) {
		return {x,y};
	} else {
		return {smallx, smally};
	}
}

int32_t main() {
	while(1) {
		int N,c1,c2,n1,n2;
		in>>N>>c1>>n1>>c2>>n2;
		if(!in || N==0) break;

		auto xy = gcd(n1, n2, N, c1, c2);
		if (xy.first<0 || xy.second<0) {
			out<<"failed\n";
		} else {
			out<<xy.first<<" "<<xy.second<<"\n";
		}
	}
}
