#include "logging.h"
#ifdef _WIN32
#include <windows.h>
#endif

namespace kekule {
	
	void setConsoleColors (const char& c) {
#ifdef _WIN32
		static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		switch (c) {
		case KEKULE_WHITE:
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			break;
		case KEKULE_YELLOW:
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);
			break;
		case KEKULE_RED:
			SetConsoleTextAttribute(h, FOREGROUND_RED);
		}
#endif
	}

	std::ostream& logI () {
#ifdef _WIN32
		setConsoleColors(KEKULE_WHITE);
		return std::cout;
#elif __linux__
		return LOGI;
#endif
	}

	std::ostream& logW () {
#ifdef _WIN32
		setConsoleColors(KEKULE_YELLOW);
		return std::cout;
#elif __linux__
		return LOGW;
#endif
	}

	std::ostream& logE () {
#ifdef _WIN32
		setConsoleColors(KEKULE_RED);
		return std::cout;
#elif __linux__
		return LOGE;
#endif
	}

}