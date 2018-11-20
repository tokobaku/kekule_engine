#include "shader.h"
#define GLEW_STATIC
#include <GL/glew.h>

namespace kekule {

	Shader Shader::mSimple;

	Shader Shader::simple () {
		if (mSimple)
			return mSimple;
		return mSimple = Shader("../src/graphics/shaders/simple.vert", "../src/graphics/shaders/simple.frag", "simple");
	}

	uint Shader::createShader (const char* src, const char* name, const uint& type) {
		GL(uint shader = glCreateShader(type));
		GL(glShaderSource(shader, 1, &src, nullptr));
		GL(glCompileShader(shader));

#ifdef KEKULE_DEBUG
		int result;
		GL(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
		if (result != GL_TRUE) {
			GL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &result));
			char* infoLog = new char[result];
			GL(glGetShaderInfoLog(shader, result, &result, infoLog));
			logError(std::string("[OpenGL] error: failed to compile shader") + name);
			logError(std::string("shader type:") +
			(type == GL_VERTEX_SHADER ? "vertex" : type == GL_FRAGMENT_SHADER ? "fragment" : "geometry"));
			logError(infoLog);
			delete[] infoLog;
		}
#endif
		return shader;
	}

	uint Shader::createProgram (const uint& vert, const uint& geomtr, const uint& frag, const char* name) {
		uint program = glCreateProgram();
		GL(glAttachShader(program, vert));
		if (geomtr) {
			GL(glAttachShader(program, geomtr));
		}
		GL(glAttachShader(program, frag));
		GL(glLinkProgram(program));

#ifdef KEKULE_DEBUG
		int result;
		GL(glGetProgramiv(program, GL_LINK_STATUS, &result));
		if (result != GL_TRUE) {
			GL(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &result));
			char* infoLog = new char[result];
			GL(glGetProgramInfoLog(program, result, &result, infoLog));
			logError(std::string("[OpenGL] error: failed to link program") + name);
			logError(infoLog);
			delete[] infoLog;
		}
#endif
		GL(glDetachShader(program, vert));
		GL(glDeleteShader(vert));
		if (geomtr) {
			GL(glDetachShader(program, geomtr));
			GL(glDeleteShader(geomtr));
		}
		GL(glDetachShader(program, frag));
		GL(glDeleteShader(frag));
		
		return program;
	}

	Shader::shader::shader (const char* vertsrc, const char* geomtrsrc, const char* fragsrc, const char* name) {
		uint vert = createShader(vertsrc, name, GL_VERTEX_SHADER);
		uint geomtr = 0;
		if (geomtrsrc != nullptr)
			geomtr = createShader(geomtrsrc, name, GL_GEOMETRY_SHADER);
		uint frag = createShader(fragsrc, name, GL_FRAGMENT_SHADER);
		this->id = createProgram(vert, geomtr, frag, name);

		int namesize = 0;
		while (name[namesize++]);	//count chars in name including \0
		this->name = new char[namesize];
		memcpy(this->name, name, sizeof(char) * namesize);
		refCount = 0;
	}

	Shader::shader::~shader () {
		if (this->id) {
			GL(glDeleteProgram(this->id));
		}
		delete[] name;
	}

	void Shader::removeRef () {
		if (mRef != nullptr) {
			mRef->refCount--;
			if (mRef->refCount < 1)
				delete mRef;
		}
	}

	Shader::Shader ()
		:mRef(nullptr) {}
	
	Shader::Shader (const char* vertpath, const char* fragpath, const char* name)
		:mRef(nullptr)
	{
		char *vertsrc = nullptr, *fragsrc = nullptr;
		try {
			read_file(vertpath, vertsrc);
			read_file(fragpath, fragsrc);
		} catch (KekuleException e) {
			logError(e.what());
			return;
		}
		mRef = new shader(vertsrc, nullptr, fragsrc, name);
		mRef->refCount++;

		delete[] vertsrc;
		delete[] fragsrc;
	}

	Shader::Shader (const char* vertpath, const char* geomtrpath, const char* fragpath, const char* name)
		:mRef(nullptr)
	{
		char *vertsrc = nullptr, *geomtrsrc = nullptr, *fragsrc = nullptr;
		try {
			read_file(vertpath, vertsrc);
			read_file(geomtrpath, geomtrsrc);
			read_file(fragpath, fragsrc);
		} catch (KekuleException e) {
			logError("Can't create shader:");
			logError(e.what());
			return;
		}
		mRef = new shader(vertsrc, geomtrsrc, fragsrc, name);
		mRef->refCount++;

		delete[] vertsrc;
		delete[] geomtrsrc;
		delete[] fragsrc;
	}

	Shader::Shader (const Shader& other) {
		mRef = other.mRef;
		if (mRef != nullptr)
			mRef->refCount++;
	}

	Shader::~Shader () {
		removeRef();
	}

	Shader& Shader::operator= (const Shader& other) {
		removeRef();
		mRef = other.mRef;
		if (mRef != nullptr)
			mRef->refCount++;
		return *this;
	}

	Shader& Shader::operator= (const nullptr_t& ptr) {
		removeRef();
		mRef = ptr;
		return *this;
	}

	bool Shader::operator== (const Shader& other) const { return mRef == other.mRef; }
	bool Shader::operator!= (const Shader& other) const { return mRef == other.mRef; }
	bool Shader::operator== (const nullptr_t& ptr) const { return mRef == ptr; }
	bool Shader::operator!= (const nullptr_t& ptr) const { return mRef == ptr; }
	Shader::operator bool () const { return mRef != nullptr; }

	std::string Shader::name () const { return mRef->name; }

	int Shader::uniformLoc (const char* uniform) const {
		if (mRef->uniforms.find(uniform) == mRef->uniforms.end()) {
			GL(int location = glGetUniformLocation(mRef->id, uniform));
			mRef->uniforms[uniform] = location;
		}
		return mRef->uniforms[uniform];
	}

	int Shader::attribLoc (const char* attrib) const {
		GL(int location = glGetAttribLocation(mRef->id, attrib));
		return location;
	}

	void Shader::bind () const {
		GL(glUseProgram(mRef == nullptr ? 0 : mRef->id));
	}

	void Shader::ubind () const {
		GL(glUseProgram(0));
	}

	void Shader::setUniform (const char* name, const float& value) const {
		this->setUniform(this->uniformLoc(name), value);
	}

	void Shader::setUniform (const char* name, const float& x, const float& y) const {
		this->setUniform(this->uniformLoc(name), vec2(x, y));
	}

	void Shader::setUniform (const char* name, const vec2& value) const {
		this->setUniform(this->uniformLoc(name), value);
	}

	void Shader::setUniform (const char* name, const float& x, const float& y, const float& z) const {
		this->setUniform(this->uniformLoc(name), vec3(x, y, z));
	}

	void Shader::setUniform (const char* name, const vec3& value) const {
		this->setUniform(this->uniformLoc(name), value);
	}

	void Shader::setUniform (const char* name, const float& x, const float& y, const float&z, const float& w) const {
		this->setUniform(this->uniformLoc(name), vec4(x, y, z, w));
	}

	void Shader::setUniform (const char* name, const vec4& value) const {
		this->setUniform(this->uniformLoc(name), value);
	}

	void Shader::setUniform (const int& location, const float& value) const {
		GL(glUniform1f(location, value));
	}

	void Shader::setUniform (const int& location, const vec2& value) const {
		GL(glUniform2f(location, value.x, value.y));
	}

	void Shader::setUniform (const int& location, const vec3& value) const {
		GL(glUniform3f(location, value.x, value.y, value.z));
	}

	void Shader::setUniform (const int& location, const vec4& value) const {
		GL(glUniform4f(location, value.x, value.y, value.z, value.w));
	}

	void Shader::setUniform (const char* name, const int& count, const float* value) const {
		this->setUniform(this->uniformLoc(name), count, value);
	}

	void Shader::setUniform (const char* name, const int& count, const vec2* value) const {
		this->setUniform(this->uniformLoc(name), count, value);
	}

	void Shader::setUniform (const char* name, const int& count, const vec3* value) const {
		this->setUniform(this->uniformLoc(name), count, value);
	}

	void Shader::setUniform (const char* name, const int& count, const vec4* value) const {
		this->setUniform(this->uniformLoc(name), count, value);
	}

	void Shader::setUniform (const int& location, const int& count, const float* value) const {
		GL(glUniform1fv(location, count, value));
	}

	void Shader::setUniform (const int& location, const int& count, const vec2* value) const {
		GL(glUniform2fv(location, count, (const float*)value));
	}

	void Shader::setUniform (const int& location, const int& count, const vec3* value) const {
		GL(glUniform3fv(location, count, (const float*)value));
	}

	void Shader::setUniform (const int& location, const int& count, const vec4* value) const {
		GL(glUniform4fv(location, count, (const float*)value));
	}

	void Shader::setUniformi (const char* name, const int& value) const {
		this->setUniformi(this->uniformLoc(name), value);
	}

	void Shader::setUniformi (const char* name, const int& x, const int& y) const {
		this->setUniformi(this->uniformLoc(name), ivec2(x, y));
	}

	void Shader::setUniformi (const char* name, const ivec2& value) const {
		this->setUniformi(this->uniformLoc(name), value);
	}

	void Shader::setUniformi (const char* name, const int& x, const int& y, const int& z) const {
		this->setUniformi(this->uniformLoc(name), ivec3(x, y, z));
	}

	void Shader::setUniformi (const char* name, const ivec3& value) const {
		this->setUniformi(this->uniformLoc(name), value);
	}

	void Shader::setUniformi (const char* name, const int& x, const int& y, const int& z, const int& w) const {
		this->setUniformi(this->uniformLoc(name), ivec4(x, y, z, w));
	}

	void Shader::setUniformi (const char* name, const ivec4& value) const {
		this->setUniformi(this->uniformLoc(name), value);
	}

	void Shader::setUniformi (const int& location, const int& value) const {
		GL(glUniform1i(location, value));
	}

	void Shader::setUniformi (const int& location, const ivec2& value) const {
		GL(glUniform2i(location, value.x, value.y));
	}

	void Shader::setUniformi (const int& location, const ivec3& value) const {
		GL(glUniform3i(location, value.x, value.y, value.z));
	}
	void Shader::setUniformi (const int& location, const ivec4& value) const {
		GL(glUniform4i(location, value.x, value.y, value.z, value.w));
	}

	void Shader::setUniformi (const char* name, const int& count, const int* value) const {
		this->setUniformi(this->uniformLoc(name), count, value);
	}

	void Shader::setUniformi (const char* name, const int& count, const ivec2* value) const {
		this->setUniformi(this->uniformLoc(name), count, value);
	}

	void Shader::setUniformi (const char* name, const int& count, const ivec3* value) const {
		this->setUniformi(this->uniformLoc(name), count, value);
	}

	void Shader::setUniformi (const char* name, const int& count, const ivec4* value) const {
		this->setUniformi(this->uniformLoc(name), count, value);
	}

	void Shader::setUniformi (const int& location, const int& count, const int* value) const {
		GL(glUniform2iv(location, count, value));
	}

	void Shader::setUniformi (const int& location, const int& count, const ivec2* value) const {
		GL(glUniform2iv(location, count, (const int*)value));
	}

	void Shader::setUniformi (const int& location, const int& count, const ivec3* value) const {
		GL(glUniform2iv(location, count, (const int*)value));
	}

	void Shader::setUniformi (const int& location, const int& count, const ivec4* value) const {
		GL(glUniform2iv(location, count, (const int*)value));
	}

	void Shader::setUniformui (const char* name, const uint& value) const {
		this->setUniformui(this->uniformLoc(name), value);
	}

	void Shader::setUniformui (const char* name, const uint& x, const uint& y) const {
		this->setUniformui(this->uniformLoc(name), uvec2(x, y));
	}

	void Shader::setUniformui (const char* name, const uvec2& value) const {
		this->setUniformui(this->uniformLoc(name), value);
	}

	void Shader::setUniformui (const char* name, const uint& x, const uint& y, const uint& z) const {
		this->setUniformui(this->uniformLoc(name), uvec3(x, y, z));
	}

	void Shader::setUniformui (const char* name, const uvec3& value) const {
		this->setUniformui(this->uniformLoc(name), value);
	}

	void Shader::setUniformui (const char* name, const uint& x, const uint& y, const uint& z, const uint& w) const {
		this->setUniformui(this->uniformLoc(name), uvec4(x, y, z, w));
	}

	void Shader::setUniformui (const char* name, const uvec4& value) const {
		this->setUniformui(this->uniformLoc(name), value);
	}

	void Shader::setUniformui (const int& location, const uint& value) const {
		GL(glUniform1ui(location, value));
	}

	void Shader::setUniformui (const int& location, const uvec2& value) const {
		GL(glUniform2ui(location, value.x, value.y));
	}

	void Shader::setUniformui (const int& location, const uvec3& value) const {
		GL(glUniform3ui(location, value.x, value.y, value.z));
	}
	void Shader::setUniformui (const int& location, const uvec4& value) const {
		GL(glUniform4ui(location, value.x, value.y, value.z, value.w));
	}

	void Shader::setUniformui (const char* name, const int& count, const uint* value) const {
		this->setUniformui(this->uniformLoc(name), count, value);
	}

	void Shader::setUniformui (const char* name, const int& count, const uvec2* value) const {
		this->setUniformui(this->uniformLoc(name), count, value);
	}

	void Shader::setUniformui (const char* name, const int& count, const uvec3* value) const {
		this->setUniformui(this->uniformLoc(name), count, value);
	}

	void Shader::setUniformui (const char* name, const int& count, const uvec4* value) const {
		this->setUniformui(this->uniformLoc(name), count, value);
	}

	void Shader::setUniformui (const int& location, const int& count, const uint* value) const {
		GL(glUniform2uiv(location, count, value));
	}

	void Shader::setUniformui (const int& location, const int& count, const uvec2* value) const {
		GL(glUniform2uiv(location, count, (const uint*)value));
	}

	void Shader::setUniformui (const int& location, const int& count, const uvec3* value) const {
		GL(glUniform2uiv(location, count, (const uint*)value));
	}

	void Shader::setUniformui (const int& location, const int& count, const uvec4* value) const {
		GL(glUniform2uiv(location, count, (const uint*)value));
	}

	void Shader::setUniformd (const char* name, const double& value) const {
		this->setUniformd(this->uniformLoc(name), value);
	}

	void Shader::setUniformd (const char* name, const double& x, const double& y) const {
		this->setUniformd(this->uniformLoc(name), dvec2(x, y));
	}

	void Shader::setUniformd (const char* name, const dvec2& value) const {
		this->setUniformd(this->uniformLoc(name), value);
	}

	void Shader::setUniformd (const char* name, const double& x, const double& y, const double& z) const {
		this->setUniformd(this->uniformLoc(name), dvec3(x, y, z));
	}

	void Shader::setUniformd (const char* name, const dvec3& value) const {
		this->setUniformd(this->uniformLoc(name), value);
	}

	void Shader::setUniformd (const char* name, const double& x, const double& y, const double& z, const double& w) const {
		this->setUniformd(this->uniformLoc(name), dvec4(x, y, z, w));
	}

	void Shader::setUniformd (const char* name, const dvec4& value) const {
		this->setUniformd(this->uniformLoc(name), value);
	}

	void Shader::setUniformd (const int& location, const double& value) const {
		GL(glUniform1d(location, value));
	}

	void Shader::setUniformd (const int& location, const dvec2& value) const {
		GL(glUniform2d(location, value.x, value.y));
	}

	void Shader::setUniformd (const int& location, const dvec3& value) const {
		GL(glUniform3d(location, value.x, value.y, value.z));
	}

	void Shader::setUniformd (const int& location, const dvec4& value) const {
		GL(glUniform4d(location, value.x, value.y, value.z, value.w));
	}

	void Shader::setUniformd (const char* name, const int& count, const double* value) const {
		this->setUniformd(this->uniformLoc(name), count, value);
	}

	void Shader::setUniformd (const char* name, const int& count, const dvec2* value) const {
		this->setUniformd(this->uniformLoc(name), count, value);
	}

	void Shader::setUniformd (const char* name, const int& count, const dvec3* value) const {
		this->setUniformd(this->uniformLoc(name), count, value);
	}

	void Shader::setUniformd (const char* name, const int& count, const dvec4* value) const {
		this->setUniformd(this->uniformLoc(name), count, value);
	}

	void Shader::setUniformd (const int& location, const int& count, const double* value) const {
		GL(glUniform1dv(location, count, value));
	}

	void Shader::setUniformd (const int& location, const int& count, const dvec2* value) const {
		GL(glUniform2dv(location, count, (const double*)value));
	}

	void Shader::setUniformd (const int& location, const int& count, const dvec3* value) const {
		GL(glUniform3dv(location, count, (const double*)value));
	}

	void Shader::setUniformd (const int& location, const int& count, const dvec4* value) const {
		GL(glUniform4dv(location, count, (const double*)value));	
	}

	void Shader::setUniformMat4 (const char* name, const mat4& value) const {
		this->setUniformMat4(this->uniformLoc(name), value);
	}

	void Shader::setUniformMat4 (const int& location, const mat4& value) const {
		glUniformMatrix4fv(location, 1, GL_FALSE, value.elements);
	}

	void Shader::setUniformMat4 (const char* name, const int& count, const mat4* matrices) const {
		this->setUniformMat4(this->uniformLoc(name), count, matrices);
	}

	void Shader::setUniformMat4 (const int& location, const int& count, const mat4* matrices) const {
		glUniformMatrix4fv(location, count, GL_FALSE, (const float*)matrices);
	}
	
}