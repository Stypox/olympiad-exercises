#include<bits/stdc++.h>
using namespace std;

int N;
int T[100000];
int memoria[100000];

int soluzione(int i) {
	if (i >= N) {
		return 0;
	}

	if (memoria[i] >= 0) {
		return memoria[i];
	}

	int sePrendoProssimo = soluzione(i+1);
	int seNonPrendoProssimo = soluzione(i+2);
	int risultato = T[i] + min(sePrendoProssimo, seNonPrendoProssimo);
	memoria[i] = risultato;
	return risultato;
}

int main() {
	cin >> N;

	for (int i = 0; i < N; i += 1) {
		cin >> T[i];
	}

	for (int i = 0; i < N; i += 1) {
		memoria[i] = -1;
	}

	int sePrendoPrimo = soluzione(0);
	int seNonPrendoPrimo = soluzione(1);
	int risultato = min(sePrendoPrimo, seNonPrendoPrimo);
	cout << risultato;
}
