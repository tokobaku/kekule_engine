#pragma once

#include <iostream>

#ifdef _WIN32
#define KEKULE_WHITE 0
#define KEKULE_YELLOW 1
#define KEKULE_RED 2

#define LOGI 	::kekule::setConsoleColors(KEKULE_WHITE); ::std::cout
#define LOGW 	::kekule::setConsoleColors(KEKULE_YELLOW); ::std::cout
#define LOGE 	::kekule::setConsoleColors(KEKULE_RED); ::std::cout
#endif

#ifdef __linux__
#define LOGI	std::cout << "\033[0;39m"
#define LOGW	std::cout << "\033[0;33m"
#define LOGE	std::cout << "\033[0;31m"
#endif

namespace kekule {
#ifdef _WIN32
	void setConsoleColors(const char& c);
#endif

	template <typename T>
	inline std::ostream& logInfo (const T& message) {
		LOGI << message << '\n';
		return std::cout;
	}

	template <typename T>
	inline std::ostream& logWarning (const T& message) {
		LOGW << message << '\n';
		return std::cout;
	}

	template <typename T>
	inline std::ostream& logError (const T& message) {
		LOGE << message;
		return std::cout;
	}

	std::ostream& logI ();
	std::ostream& logW ();
	std::ostream& logE ();
}