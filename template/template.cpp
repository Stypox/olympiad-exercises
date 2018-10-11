#include <bits/stdc++.h>
#ifdef __linux__
#include <sys/stat.h>
#endif

namespace io {
	class Input {
	#ifndef USE_STDIN
		char* m_data;
		const char* m_dataBegin;
	#endif
	public:
		inline __attribute__((always_inline)) Input();
		inline __attribute__((always_inline)) ~Input();
		template <typename T> inline __attribute__((always_inline)) Input& operator>> (T& data);
		inline __attribute__((always_inline)) Input& operator>> (std::nullptr_t);
	} in;

	class Output {
	#ifndef USE_STDOUT
		std::FILE* m_file;
	#endif
	public:
		inline __attribute__((always_inline)) Output();
		inline __attribute__((always_inline)) ~Output();
		template <typename T> inline __attribute__((always_inline)) Output& operator<< (const T& data);
	} out;
}

using i = long long;
using ui = unsigned long long;
using f = long double;
using io::in;
using io::out;

int main() {
	
}

namespace io {
	constexpr const char* inputFilename = "input.txt", * outputFilename = "output.txt";

	template<typename T> struct to_format;
	template<>         struct to_format<signed   char     > { static constexpr const char * format = "%hhd "; };
	template<>         struct to_format<unsigned char     > { static constexpr const char * format = "%hhu "; };
	template<>         struct to_format<signed   short    > { static constexpr const char * format = "%hd ";  };
	template<>         struct to_format<unsigned short    > { static constexpr const char * format = "%hu ";  };
	template<>         struct to_format<signed   int      > { static constexpr const char * format = "%d ";   };
	template<>         struct to_format<unsigned int      > { static constexpr const char * format = "%u ";   };
	template<>         struct to_format<signed   long     > { static constexpr const char * format = "%ld ";  };
	template<>         struct to_format<unsigned long     > { static constexpr const char * format = "%lu ";  };
	template<>         struct to_format<signed   long long> { static constexpr const char * format = "%lld "; };
	template<>         struct to_format<unsigned long long> { static constexpr const char * format = "%llu "; };
	template<>         struct to_format<float             > { static constexpr const char * format = "%f ";   };
	template<>         struct to_format<double            > { static constexpr const char * format = "%f ";   };
	template<>         struct to_format<long double       > { static constexpr const char * format = "%Lf ";  };
	template<>         struct to_format<const char*       > { static constexpr const char * format = "%s ";   };
	template<>         struct to_format<      char*       > { static constexpr const char * format = "%s ";   };
	template<size_t n> struct to_format<      char[n]     > { static constexpr const char * format = "%s ";   };

	template<typename T> T read(char*& str);
	template<> inline __attribute__((always_inline)) signed   char      read<signed   char     >(char*& str) { return std::strtol  (str, &str, 0); }
	template<> inline __attribute__((always_inline)) unsigned char      read<unsigned char     >(char*& str) { return std::strtoul (str, &str, 0); }
	template<> inline __attribute__((always_inline)) signed   short     read<signed   short    >(char*& str) { return std::strtol  (str, &str, 0); }
	template<> inline __attribute__((always_inline)) unsigned short     read<unsigned short    >(char*& str) { return std::strtoul (str, &str, 0); }
	template<> inline __attribute__((always_inline)) signed   int       read<signed   int      >(char*& str) { return std::strtol  (str, &str, 0); }
	template<> inline __attribute__((always_inline)) unsigned int       read<unsigned int      >(char*& str) { return std::strtoul (str, &str, 0); }
	template<> inline __attribute__((always_inline)) signed   long      read<signed   long     >(char*& str) { return std::strtol  (str, &str, 0); }
	template<> inline __attribute__((always_inline)) unsigned long      read<unsigned long     >(char*& str) { return std::strtoul (str, &str, 0); }
	template<> inline __attribute__((always_inline)) signed   long long read<signed   long long>(char*& str) { return std::strtoll (str, &str, 0); }
	template<> inline __attribute__((always_inline)) unsigned long long read<unsigned long long>(char*& str) { return std::strtoull(str, &str, 0); }
	template<> inline __attribute__((always_inline)) float              read<float             >(char*& str) { return std::strtof  (str, &str   ); }
	template<> inline __attribute__((always_inline)) double             read<double            >(char*& str) { return std::strtod  (str, &str   ); }
	template<> inline __attribute__((always_inline)) long double        read<long double       >(char*& str) { return std::strtold (str, &str   ); }
	template<> inline __attribute__((always_inline)) std::string        read<std::string       >(char*& str) {
		while (isspace(*str)) ++str;
		if (*str == '\0') return "";

		char* begin = str;
		do { ++str; }
		while (!isspace(*str) && *str != '\0');

		return std::string{begin, static_cast<unsigned long>(str-begin)};
	}
	template<> inline __attribute__((always_inline)) void               read<void              >(char*& str) {
		while (isspace(*str)) ++str;
		if (*str == '\0') return;

		do { ++str; }
		while (!isspace(*str) && *str != '\0');
	}


#ifdef USE_STDIN
	inline __attribute__((always_inline)) Input::Input() {
	#ifndef DEBUG
		std::cin.sync_with_stdio(false);
	#endif
	}
	inline __attribute__((always_inline)) Input::~Input() {}
	template <typename T> inline __attribute__((always_inline)) Input& Input::operator>> (T& data) {
		std::cin >> data;
		return *this;
	}
	inline __attribute__((always_inline)) Input& Input::operator>> (std::nullptr_t) {
		std::string s;
		std::cin >> s;
		return *this;
	}
#else
	inline __attribute__((always_inline)) Input::Input() {
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
	inline __attribute__((always_inline)) Input::~Input() {
	#ifdef DEBUG // leaking memory is not bad, because it reduces time.
		delete m_dataBegin;
	#endif
	}
	template <typename T> inline __attribute__((always_inline)) Input& Input::operator>> (T& data) {
		data = read<T>(m_data);
		return *this;
	}
	inline __attribute__((always_inline)) Input& Input::operator>> (std::nullptr_t) {
		read<void>(m_data);
		return *this;
	}
#endif

#ifdef USE_STDOUT
	inline __attribute__((always_inline)) Output::Output() {}
	inline __attribute__((always_inline)) Output::~Output() {}
	template <typename T> inline __attribute__((always_inline)) Output& Output::operator<< (const T& data) {
		std::printf(to_format<T>::format, data);
		return *this;
	}
#else
	inline __attribute__((always_inline)) Output::Output() : m_file{fopen(outputFilename, "w")} {
	#ifdef DEBUG
		if (!m_file) {
			perror(("Unable to open file " + std::string{outputFilename}).c_str());
			exit(1);
		}
	#endif
	}
	inline __attribute__((always_inline)) Output::~Output() {
		fclose(m_file);
	}
	template <typename T> inline __attribute__((always_inline)) Output& Output::operator<< (const T& data) {
		std::fprintf(m_file, to_format<T>::format, data);
		return *this;
	}
#endif
	template <> inline __attribute__((always_inline)) Output& Output::operator<< (const std::string& data) {
		this->operator<<(data.c_str());
		return *this;
	}
}