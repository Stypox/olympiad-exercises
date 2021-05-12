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

constexpr int8_t G = 0, S = 1, C = 2, B = 3;
struct Card {
	int8_t type, value;
};
istream& operator>>(istream& input, Card& card) {
	string data;
	input >> data;

	char typeCh;
	if (data[1] == '0') {
		assert(data[0] == '1');
		card.value = 10;
		typeCh = data[2];
	}
	else {
		card.value = data[0] - '0';
		typeCh = data[1];
	}

	if (typeCh == 'G')
		card.type = G;
	else if (typeCh == 'S')
		card.type = S;
	else if (typeCh == 'C')
		card.type = C;
	else if (typeCh == 'B')
		card.type = B;
	else
		assert(false);

	return input;
}
ostream& operator<<(ostream& output, Card& card) {
	output << (int)card.value;

	if (card.type == G)
		output << "G";
	if (card.type == S)
		output << "S";
	if (card.type == C)
		output << "C";
	if (card.type == B)
		output << "B";

	output << " ";
	return output;
}
bool operator==(const Card& a, const Card& b) {
	return a.type == b.type && a.value == b.value;
}

int8_t sumAll(const vector<Card>& table) {
	int8_t sum = 0;
	for (auto&& c : table)
		sum += c.value;
	return sum;
}
bool removeIfEqual(int8_t value, vector<Card>& hand) {
	for(auto it = hand.begin(); it != hand.end(); ++it) {
		if(it->value == value) {
			out << *it;
			return true;
		}
	}
	return false;
}
bool remove4IfSumUpTo(int8_t value, vector<Card>& table) {
	if (sumAll(table) == value) {
		for(auto&& c : table)
			out << c;
		return true;
	}
	return false;
}
bool remove3IfSumUpTo(int8_t value, vector<Card>& table) {
	for(auto it1 = table.begin(); it1 != table.end() - 2; ++it1) {
		for(auto it2 = it1 + 1; it2 != table.end() - 1; ++it2) {
			for(auto it3 = it2 + 1; it3 != table.end(); ++it3) {
				if(it1->value + it2->value + it3->value == value) {
					out << *it1 << *it2 << *it3;
					return true;
				}
			}
		}
	}
	return false;
}
bool remove2IfSumUpTo(int8_t value, vector<Card>& table) {
	for(auto it1 = table.begin(); it1 != table.end() - 1; ++it1) {
		for(auto it2 = it1 + 1; it2 != table.end(); ++it2) {
			if(it1->value + it2->value == value) {
				out << *it1 << *it2;
				return true;
			}
		}
	}
	return false;
}
bool removeIfSumUpTo(int8_t value, vector<Card>& table) {
	return remove4IfSumUpTo(value, table) ||
		remove3IfSumUpTo(value, table) ||
		remove2IfSumUpTo(value, table) ||
		removeIfEqual(value, table);
}

bool trySetteBelloHand(vector<Card>& hand, vector<Card>& table) {
	for(auto it = hand.begin(); it != hand.end(); ++it) {
		if(*it == Card{G, 7}) {
			if (removeIfEqual(7, table) || removeIfSumUpTo(7, table)) {
				out << *it;
				return true;
			}
		}
	}
	return false;
}

bool tryScopa(vector<Card>& hand, vector<Card>& table) {
	bool res = removeIfEqual(sumAll(table), hand);
	if (res) {
		for(auto&& c : table)
			out << c;
	}
	return res;
}

bool trySetteBelloTable(vector<Card>& hand, vector<Card>& table) {
	for(auto it = table.begin(); it != table.end(); ++it) {
		if(*it == Card{G, 7}) {
			if (removeIfEqual(7, hand)) {
				out << *it;
				return true;
			}
		}
	}
	return false;
}

bool trySeven(vector<Card>& hand, vector<Card>& table) {
	for(auto it = hand.begin(); it != hand.end(); ++it) {
		if (it->value == 7 && remove4IfSumUpTo(it->value, table)) {
			out << *it;
			return true;
		}
	}
	for(auto it = hand.begin(); it != hand.end(); ++it) {
		if (it->value == 7 && removeIfEqual(7, table)) {
			out << *it;
			return true;
		}
	}
	for(auto it = hand.begin(); it != hand.end(); ++it) {
		if (it->value == 7 && remove3IfSumUpTo(it->value, table)) {
			out << *it;
			return true;
		}
	}
	for(auto it = hand.begin(); it != hand.end(); ++it) {
		if (it->value == 7 && remove2IfSumUpTo(it->value, table)) {
			out << *it;
			return true;
		}
	}

	return false;
}

bool otherwise(vector<Card>& hand, vector<Card>& table) {
	for(auto it = hand.begin(); it != hand.end(); ++it) {
		if (remove4IfSumUpTo(it->value, table)) {
			out << *it;
			return true;
		}
	}
	for(auto it = hand.begin(); it != hand.end(); ++it) {
		if (remove3IfSumUpTo(it->value, table)) {
			out << *it;
			return true;
		}
	}
	for(auto it = hand.begin(); it != hand.end(); ++it) {
		if (remove2IfSumUpTo(it->value, table)) {
			out << *it;
			return true;
		}
	}
	for(auto it = hand.begin(); it != hand.end(); ++it) {
		if (removeIfEqual(it->value, table)) {
			out << *it;
			return true;
		}
	}
	return false;
}

signed main() {
	vector<Card> hand(3), table(4);
	for(auto& c : hand)
		in >> c;
	for(auto& c : table)
		in >> c;

	assert(trySetteBelloHand(hand, table) ||
	tryScopa(hand, table) ||
	trySetteBelloTable(hand, table) ||
	trySeven(hand, table) ||
	otherwise(hand, table));

	return 0;
}

