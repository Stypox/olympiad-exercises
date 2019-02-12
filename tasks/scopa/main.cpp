#pragma region
#ifndef DEBUG
#pragma GCC optimize ("O3")
#endif
#include <bits/stdc++.h>

#define WORD_SEPARATOR ""
using i = long long;
using ui = unsigned long long;
using f = long double;
using ch = char;
using str = std::string;
template <typename T> using vec = std::vector<T>;
template <typename T, size_t N> using arr = std::array<T, N>;

#ifdef __linux__
#include <sys/stat.h>
#endif
#define INLINE inline __attribute__((always_inline))

namespace io {
	class Input {
	#ifndef USE_STDIN
		char* m_data;
		const char* m_dataBegin;
	#endif
	public:
		INLINE Input();
		INLINE ~Input();
		template <typename T> INLINE Input& operator>> (T& data);
		INLINE Input& operator>> (std::nullptr_t);
	} in;

	class Output {
	#ifndef USE_STDOUT
		std::FILE* m_file;
	#endif
	public:
		INLINE Output();
		INLINE ~Output();
		template <typename T> INLINE Output& operator<< (const T& data);
	} out;


	constexpr const char* inputFilename = "input.txt", * outputFilename = "output.txt";

	template<typename T> struct to_format;
	template<>         struct to_format<signed   char     > { static constexpr const char * format = "%hhd" WORD_SEPARATOR; };
	template<>         struct to_format<unsigned char     > { static constexpr const char * format = "%hhu" WORD_SEPARATOR; };
	template<>         struct to_format<signed   short    > { static constexpr const char * format = "%hd"  WORD_SEPARATOR; };
	template<>         struct to_format<unsigned short    > { static constexpr const char * format = "%hu"  WORD_SEPARATOR; };
	template<>         struct to_format<signed   int      > { static constexpr const char * format = "%d"   WORD_SEPARATOR; };
	template<>         struct to_format<unsigned int      > { static constexpr const char * format = "%u"   WORD_SEPARATOR; };
	template<>         struct to_format<signed   long     > { static constexpr const char * format = "%ld"  WORD_SEPARATOR; };
	template<>         struct to_format<unsigned long     > { static constexpr const char * format = "%lu"  WORD_SEPARATOR; };
	template<>         struct to_format<signed   long long> { static constexpr const char * format = "%lld" WORD_SEPARATOR; };
	template<>         struct to_format<unsigned long long> { static constexpr const char * format = "%llu" WORD_SEPARATOR; };
	template<>         struct to_format<float             > { static constexpr const char * format = "%f"   WORD_SEPARATOR; };
	template<>         struct to_format<double            > { static constexpr const char * format = "%f"   WORD_SEPARATOR; };
	template<>         struct to_format<long double       > { static constexpr const char * format = "%Lf"  WORD_SEPARATOR; };
	template<>         struct to_format<const char*       > { static constexpr const char * format = "%s"   WORD_SEPARATOR; };
	template<>         struct to_format<      char*       > { static constexpr const char * format = "%s"   WORD_SEPARATOR; };
	template<size_t n> struct to_format<      char[n]     > { static constexpr const char * format = "%s"   WORD_SEPARATOR; };

	template<typename T> T read(char*& str);
	template<> INLINE signed   char      read<signed   char     >(char*& str) { return std::strtol  (str, &str, 0); }
	template<> INLINE unsigned char      read<unsigned char     >(char*& str) { return std::strtoul (str, &str, 0); }
	template<> INLINE signed   short     read<signed   short    >(char*& str) { return std::strtol  (str, &str, 0); }
	template<> INLINE unsigned short     read<unsigned short    >(char*& str) { return std::strtoul (str, &str, 0); }
	template<> INLINE signed   int       read<signed   int      >(char*& str) { return std::strtol  (str, &str, 0); }
	template<> INLINE unsigned int       read<unsigned int      >(char*& str) { return std::strtoul (str, &str, 0); }
	template<> INLINE signed   long      read<signed   long     >(char*& str) { return std::strtol  (str, &str, 0); }
	template<> INLINE unsigned long      read<unsigned long     >(char*& str) { return std::strtoul (str, &str, 0); }
	template<> INLINE signed   long long read<signed   long long>(char*& str) { return std::strtoll (str, &str, 0); }
	template<> INLINE unsigned long long read<unsigned long long>(char*& str) { return std::strtoull(str, &str, 0); }
	template<> INLINE float              read<float             >(char*& str) { return std::strtof  (str, &str   ); }
	template<> INLINE double             read<double            >(char*& str) { return std::strtod  (str, &str   ); }
	template<> INLINE long double        read<long double       >(char*& str) { return std::strtold (str, &str   ); }
	template<> INLINE std::string        read<std::string       >(char*& str) {
		while (isspace(*str)) ++str;
		if (*str == '\0') return "";

		char* begin = str;
		do { ++str; }
		while (!isspace(*str) && *str != '\0');

		return std::string{begin, static_cast<unsigned long>(str-begin)};
	}
	template<> INLINE void               read<void              >(char*& str) {
		while (isspace(*str)) ++str;
		if (*str == '\0') return;

		do { ++str; }
		while (!isspace(*str) && *str != '\0');
	}


#ifdef USE_STDIN
	INLINE Input::Input() {
	#ifndef DEBUG
		std::cin.sync_with_stdio(false);
	#endif
	}
	INLINE Input::~Input() {}
	template <typename T> INLINE Input& Input::operator>> (T& data) {
		std::cin >> data;
		return *this;
	}
	INLINE Input& Input::operator>> (std::nullptr_t) {
		std::string s;
		std::cin >> s;
		return *this;
	}
#else
	INLINE Input::Input() {
		std::FILE* file = fopen(inputFilename, "r");
	#ifdef DEBUG
		if (!file) {
			perror(("Unable to open file " + std::string{inputFilename}).c_str());
			exit(1);
		}
	#endif
	#ifdef __linux__
		struct stat info;
		fstat(fileno(file), &info);
		size_t size = info.st_size;
	#else
		fseek(file, 0, SEEK_END);
		size_t size = ftell(file);
		fseek(file, 0, SEEK_SET);
	#endif

		m_data = new char[size + 1];
		m_dataBegin = m_data;
		m_data[size] = '\0';

		fread(m_data, sizeof(char), size, file);
		fclose(file);
	}
	INLINE Input::~Input() {
	#ifdef DEBUG // leaking memory is not bad, because it reduces time.
		delete[] m_dataBegin;
	#endif
	}
	template <typename T> INLINE Input& Input::operator>> (T& data) {
		data = read<T>(m_data);
		return *this;
	}
	INLINE Input& Input::operator>> (std::nullptr_t) {
		read<void>(m_data);
		return *this;
	}
#endif

#ifdef USE_STDOUT
	INLINE Output::Output() {}
	INLINE Output::~Output() {}
	template <typename T> INLINE Output& Output::operator<< (const T& data) {
		std::printf(to_format<T>::format, data);
		return *this;
	}
#else
	INLINE Output::Output() : m_file{fopen(outputFilename, "w")} {
	#ifdef DEBUG
		if (!m_file) {
			perror(("Unable to open file " + std::string{outputFilename}).c_str());
			exit(1);
		}
	#endif
	}
	INLINE Output::~Output() {
		fclose(m_file);
	}
	template <typename T> INLINE Output& Output::operator<< (const T& data) {
		std::fprintf(m_file, to_format<T>::format, data);
		return *this;
	}
#endif
	template <> INLINE Output& Output::operator<< (const std::string& data) {
		this->operator<<(data.c_str());
		return *this;
	}
}
using io::in;
using io::out;
#pragma endregion

constexpr int8_t G = 0, S = 1, C = 2, B = 3;
struct Card {
	int8_t type, value;
};
io::Input& operator>>(io::Input& input, Card& card) {
	str data;
	input >> data;
	if (data[1] == 'G')
		card.type = G;
	else if (data[1] == 'S')
		card.type = S;
	else if (data[1] == 'C')
		card.type = C;
	else if (data[1] == 'B')
		card.type = B;

	card.value = data[0] - '0';
	return input;
}
io::Output& operator<<(io::Output& output, Card& card) {
	output << card.value;

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

int8_t sumAll(const vec<Card>& table) {
	int8_t sum = 0;
	for (auto&& c : table)
		sum += c.value;
	return sum;
}
bool removeIfEqual(int8_t value, vec<Card>& hand) {
	for(auto it = hand.begin(); it != hand.end(); ++it) {
		if(it->value == value) {
			out << *it;
			return true;
		}
	}
	return false;
}
bool remove4IfSumUpTo(int8_t value, vec<Card>& table) {
	if (sumAll(table) == value) {
		for(auto&& c : table)
			out << c;
		return true;
	}
	return false;
}
bool remove3IfSumUpTo(int8_t value, vec<Card>& table) {
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
bool remove2IfSumUpTo(int8_t value, vec<Card>& table) {
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
bool removeIfSumUpTo(int8_t value, vec<Card>& table) {
	return remove4IfSumUpTo(value, table) ||
		remove3IfSumUpTo(value, table) ||
		remove2IfSumUpTo(value, table) ||
		removeIfEqual(value, table);
}

bool trySetteBelloHand(vec<Card>& hand, vec<Card>& table) {
	for(auto it = hand.begin(); it != hand.end(); ++it) {
		if(*it == Card{G, 7}) {
			if (removeIfEqual(7, table)) {
				out << *it;
				return true;
			}
			if (removeIfSumUpTo(7, table)) {
				out << *it;
				return true;
			}
		}
	}
	return false;
}

bool tryScopa(vec<Card>& hand, vec<Card>& table) {
	bool res = removeIfEqual(sumAll(table), hand);
	if (res) {
		for(auto&& c : table)
			out << c;
	}
	return res;
}

bool trySetteBelloTable(vec<Card>& hand, vec<Card>& table) {
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

bool trySeven(vec<Card>& hand, vec<Card>& table) {
	for(auto it = hand.begin(); it != hand.end(); ++it) {
		if(it->value == 7) {
			if (removeIfSumUpTo(7, table)) {
				out << *it;
				return true;
			}
		}
	}
	return false;
}

bool otherwise(vec<Card>& hand, vec<Card>& table) {
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

int main() {
	vec<Card> hand(3), table(4);
	for(auto& c : hand)
		in >> c;
	for(auto& c : table)
		in >> c;
	
	trySetteBelloHand(hand, table) ||
	tryScopa(hand, table) ||
	trySetteBelloTable(hand, table) ||
	trySeven(hand, table) ||
	otherwise(hand, table);

	return 0;
}
