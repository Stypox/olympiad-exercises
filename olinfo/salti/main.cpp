#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

unsigned int count_1bits(unsigned int x) {
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x0000003F;
}

int main() {
	auto input = fopen("input.txt","r");
	fseek(input,0,SEEK_END);
	int size = ftell(input);

	int buffer[13];
	fseek(input,0,SEEK_SET);
   fread(buffer,size,1,input);
	int N;
	cin>>N;

	int sum = 0;
	while (N != 0) {
		sum += (N % 2);
		N >>= 1;
	}

	out << count_1bits(N);
}
