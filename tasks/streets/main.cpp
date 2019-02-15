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

struct City {
	i budget, nrStreets = 0;
	float ratio() {
		if (budget >= nrStreets && budget != 0)
			return 1.5f;
		return (float)budget/nrStreets;
	}
};
struct Street {
	i from, to;
	float coefficient = 0.0f;

	Street(i a, i b);
	void build();
	void updateCoefficient();

	bool operator<(const Street& s) {
		return coefficient < s.coefficient;
	}
};

vec<City> cities;
vec<Street> streets;

Street::Street(i a, i b) :
from{a}, to{b} {
	++cities[from].nrStreets;
	++cities[to].nrStreets;
}
void Street::build() {
	--cities[from].budget;
	--cities[to].budget;
	--cities[from].nrStreets;
	--cities[to].nrStreets;
	out << from << " " << to << "\n";
}
void Street::updateCoefficient() {
	float a = cities[from].ratio();
	float b = cities[to].ratio();
	if (a == 0.0f || b == 0.0f)
		coefficient = -1.0f;
	else
		coefficient = a + b;
}

int main() {
	i N, M;
	in >> N >> M;

	cities.resize(N);
	for(auto& city : cities)
		in >> city.budget;
	
	streets.reserve(M);
	for(int m = 0; m != M; ++m) {
		i a, b;
		in >> a >> b;
		streets.push_back({a, b});
	}

	while(1) {
		for(auto& s : streets) s.updateCoefficient();
		streets.erase(std::remove_if(streets.begin(), streets.end(), [](Street& s){ return s.coefficient < 0.0f; }), streets.end());
		if (streets.empty()) break;

		auto bestStreet = std::max_element(streets.begin(), streets.end());
		bestStreet->build();
		streets.erase(bestStreet);
	}	

	return 0;
}
