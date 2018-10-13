#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif
#include <initializer_list>
#include <iostream>

namespace kekule {

	//display message in white text ('std::cout <<' operator must be overloaded for type T)
	template <typename T>
	void logInfo (const T& message) {
#ifdef _WIN32
		static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 15);
#endif
		std::cout << message << '\n';
	}

	//display message in yellow text ('std::cout <<' operator must be overloaded for type T)
	template <typename T>
	void logWarning (const T& message) {
#ifdef _WIN32
		static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 14);
#endif
		std::cout << message << '\n';
#ifdef _WIN32	//reset text colors
		SetConsoleTextAttribute(h, 15);
#endif
	}

	//display message in red text ('std::cout <<' operator must be overloaded for type T)
	template <typename T>
	void logError (const T& message) {
#ifdef _WIN32
		static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 12);
#endif
		std::cout << message << '\n';
#ifdef _WIN32	//reset text colors
		SetConsoleTextAttribute(h, 15);
#endif
	}

}