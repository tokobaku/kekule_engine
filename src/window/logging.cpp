#include "logging.h"
#include <windows.h>

namespace kekule {
	
	void setConsoleColors (const char& c) {
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
	}

	std::ostream& logI () { setConsoleColors(KEKULE_WHITE); return std::cout; }
	std::ostream& logW () { setConsoleColors(KEKULE_YELLOW); return std::cout; }
	std::ostream& logE () { setConsoleColors(KEKULE_RED); return std::cout; }

}