#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "logging.h"
#include <fstream>
#include <exception>
#include <string.h>

namespace kekule {

	inline bool read_file (const char* path, char*& buffer) {
		FILE* file = fopen(path, "rt");
		if (!file) {
			buffer = nullptr;
			LOGE << "[kekule_engine] failed to open file: " << path << '\n';
			return false;
		}
		fseek(file, 0, SEEK_END);
		long size = ftell(file);
		size++;
		fseek(file, 0, SEEK_SET);
		buffer = new char[size];
		memset(buffer, 0, sizeof(char) * size);
		fread(buffer, 1, size * sizeof(char), file);
		fclose(file);
		return true;
	}

	typedef unsigned int uint;

	inline void logGlError (const int& line, const char* linestr, const char* filestr, const int& err) {
		LOGE << "[OpenGL] error: in file " << filestr << ", at line " << line << ", error code: " << err << '\n';
	}

#ifdef KEKULE_DEBUG
	#define GL(x) while(glGetError() != GL_NO_ERROR); x; logGlError(__LINE__, #x, __FILE__, err)
#else
	#define GL(x) x
#endif
	
	
}