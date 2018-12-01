#pragma once

#include <iostream>

#define KEKULE_WHITE 0
#define KEKULE_YELLOW 1
#define KEKULE_RED 2

#define LOGI 	::kekule::setConsoleColors(KEKULE_WHITE); ::std::cout
#define LOGW 	::kekule::setConsoleColors(KEKULE_YELLOW); ::std::cout
#define LOGE 	::kekule::setConsoleColors(KEKULE_RED); ::std::cout

namespace kekule {
	void setConsoleColors(const char& c);

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