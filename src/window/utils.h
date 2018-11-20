#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "logging.h"
#include <fstream>
#include <exception>
#include <string>

namespace kekule {

	class KekuleException : public std::exception {
	private:
		std::string mMessage;
	public:
		inline KekuleException () {}
		
		KekuleException (std::string& message)
			:mMessage(message) {}

		inline KekuleException (const KekuleException& other)
			:mMessage(other.mMessage) {}

		inline ~KekuleException () {}

		inline const char* what () const noexcept override {
			return mMessage.c_str();
		}
	};

	inline void read_file (const char* path, char*& buffer) {
		FILE* file = fopen(path, "rt");
		if (!file) {
			std::string message = "failed to open file ";
			message += path;
			throw KekuleException(message);
		}
		fseek(file, 0, SEEK_END);
		long size = ftell(file);
		size++;
		fseek(file, 0, SEEK_SET);
		buffer = new char[size];
		memset(buffer, 0, sizeof(char) * size);
		fread(buffer, 1, size * sizeof(char), file);
		fclose(file);
	}

	typedef unsigned int uint;

	inline void logGlError (const int& line, const char* linestr, const char* filestr, const int& err) {
		logError("------------[OpenGL] error------------");
		logError(line);
		logError(linestr);
		logError(filestr);
		logError(err);
	}

#ifdef KEKULE_DEBUG
	#define GL(x) while(glGetError() != GL_NO_ERROR); x; logGlError(__LINE__, #x, __FILE__, err)
#else
	#define GL(x) x
#endif
	
	
}