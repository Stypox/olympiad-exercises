#include <bits/stdc++.h>

#define DEBUG 0

using std::cin;
#if DEBUG
using std::cout;
#endif
using std::get;
using std::fstream;

using i = long long;
using ch = char;
using str = std::string;
using vec = std::vector<str>;
using map = std::map<str, i>;
using pair = std::pair<str, i>;

inline void subtract(ch& letter, ch n) {
	constexpr ch AtoZ = 26;
	ch subtracted = letter - n;
	letter = (subtracted >= 'a') ? (subtracted) : (subtracted + AtoZ);
}

inline void normalize(str& string) {
	ch toSubtract = string[0] - 'a';
	for (auto&& letter : string)
		subtract(letter, toSubtract);
}

inline i caesar(vec& strings) {
	map seenStrings;
	for (auto&& string : strings) {
		normalize(string);
		++seenStrings[string];
	}
	return get<1>(*std::max_element(seenStrings.begin(), seenStrings.end(), [](const pair& a, const pair& b) {
		return get<1>(a) < get<1>(b);
	}));
}

int main() {
	fstream cin ("input.txt", std::ios::in);
	#if !DEBUG
	fstream cout ("output.txt", std::ios::out);
	#endif
	
	i N, D;
	cin >> N >> D;
	
	str string;
	vec strings;
	strings.reserve(N);
	for (i n = 0; n < N; ++n) {
		cin >> string;
		strings.push_back(string);
	}
	
	cout << caesar(strings);
	return 0;
}