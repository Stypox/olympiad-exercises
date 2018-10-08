#include <cstdio>
#include <cstddef>
#include <type_traits>
#include <math.h>
#include <string>
#define DEBUG
#define USE_STDIN
#define USE_STDOUT

using i = long long;
using ui = unsigned long long;
using f = long double;

#pragma region
template<typename T> struct to_format           { static constexpr const char * format = nullptr; };
template<> struct to_format<signed   char     > { static constexpr const char * format = "%hhd";  };
template<> struct to_format<unsigned char     > { static constexpr const char * format = "%hhu";  };
template<> struct to_format<signed   short    > { static constexpr const char * format = "%hd";   };
template<> struct to_format<unsigned short    > { static constexpr const char * format = "%hu";   };
template<> struct to_format<signed   int      > { static constexpr const char * format = "%d";    };
template<> struct to_format<unsigned int      > { static constexpr const char * format = "%u";    };
template<> struct to_format<signed   long     > { static constexpr const char * format = "%ld";   };
template<> struct to_format<unsigned long     > { static constexpr const char * format = "%lu";   };
template<> struct to_format<signed   long long> { static constexpr const char * format = "%lld";  };
template<> struct to_format<unsigned long long> { static constexpr const char * format = "%llu";  };
template<> struct to_format<float             > { static constexpr const char * format = "%f";    };
template<> struct to_format<double            > { static constexpr const char * format = "%f";    };
template<> struct to_format<long double       > { static constexpr const char * format = "%Lf";   };
#pragma endregion
#pragma region
class Input {
#ifdef USE_STDIN
public:
	Input() {}
	template <typename T> inline Input& operator>> (T& data) {
		static_assert(to_format<T>::format != nullptr);
	#ifdef DEBUG
		while (0 >= std::scanf(to_format<T>::format, &data));
	#else
		std::scanf(to_format<T>::format, &data);
	#endif
		return *this;
	}
#else
	std::FILE* m_file;
public:
	Input() : m_file{fopen("input.txt", "r")} {
	#ifdef DEBUG
		if (!m_file) {
			perror("Unable to open file \"input.txt\"");
			exit(1);
		}
	#endif
	}
	template <typename T> inline Input& operator>> (T& data) {
		static_assert(to_format<T>::format != nullptr);
		std::fscanf(m_file, to_format<T>::format, &data);
		return *this;
	}
#endif
} in;
#pragma endregion
#pragma region
class Output {
#ifdef USE_STDOUT
public:
	Output() {}
	template <typename T> inline Output& operator<< (T data) {
		if constexpr(to_format<T>::format)
			std::printf(to_format<T>::format, data);
		#ifdef DEBUG
		else if constexpr(std::is_same<T, const char *>::value)
			std::printf("%s", data);
		#endif
		return *this;
	}
#else
	std::FILE* m_file;
public:
	Output() : m_file{fopen("output.txt", "w")} {
	#ifdef DEBUG
		if (!m_file) {
			perror("Unable to open file \"input.txt\"");
			exit(1);
		}
	#endif
	}
#endif
} out;
#pragma endregion

constexpr ui squareNumbers(ui a, ui b) {
	f sqrtA = sqrt(a), sqrtB = sqrt(b);

	if (a == static_cast<ui>(sqrtA) * static_cast<ui>(sqrtA))
		return floor(sqrtB - sqrtA) + 1;
	else
		return round(sqrtB - sqrtA);
}

int main() {
	ui a, b;
	in >> a >> b;
	out << squareNumbers(a, b);
}