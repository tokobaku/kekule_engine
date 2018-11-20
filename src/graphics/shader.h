#pragma once

#include "../window/utils.h"
#include "../maths/kmath.h"
#include <string>
#include <unordered_map>
#include <set>

namespace kekule {

	class Shader {
	private:
		static uint createShader (const char* src, const char* name, const uint& type);
		static uint createProgram (const uint& vert, const uint& geomtr, const uint& frag, const char* name);

		class shader {
		public:
			uint id;
			mutable uint refCount;
			mutable std::unordered_map<std::string, int> uniforms;
			char* name;

			shader () = delete;
			shader (const char* vertsrc, const char* geomtrsrc, const char* fragsrc, const char* name);
			~shader ();
		};

		mutable shader* mRef;
		void removeRef ();

		static Shader mSimple;
	public:
		static Shader simple ();
	
		Shader ();
		Shader (const char* vertpath, const char* fragpath, const char* name);
		Shader (const char* vertpath, const char* geomtrpath, const char* fragpath, const char* name);
		Shader (const Shader& other);
		~Shader ();

		Shader& operator= (const Shader& other);
		Shader& operator= (const nullptr_t& ptr);
		
		bool operator== (const Shader& other) const;
		bool operator!= (const Shader& other) const;
		bool operator== (const nullptr_t& ptr) const;
		bool operator!= (const nullptr_t& ptr) const;
		operator bool () const;

		static Shader fromSource (const char* vertsrc, const char* fragsrc, const char* name);
		static Shader fromSource (const char* vertsrc, const char* geomtrsrc, const char* fragsrc, const char* name);

		std::string name () const;
		int uniformLoc (const char* uniform) const;
		int attribLoc (const char* attrib) const;

		void bind () const;
		void ubind () const;

		void setUniform (const char* name, const float& value) const;
		void setUniform (const char* name, const float& x, const float& y) const;
		void setUniform (const char* name, const vec2& value) const;
		void setUniform (const char* name, const float& x, const float& y, const float& z) const;
		void setUniform (const char* name, const vec3& value) const;
		void setUniform (const char* name, const float& x, const float& y, const float& z, const float& w) const;
		void setUniform (const char* name, const vec4& value) const;
		void setUniform (const int& location, const float& value) const;
		void setUniform (const int& location, const vec2& value) const;
		void setUniform (const int& location, const vec3& value) const;
		void setUniform (const int& location, const vec4& value) const;

		void setUniform (const char* name, const int& count, const float* value) const;
		void setUniform (const char* name, const int& count, const vec2* value) const;
		void setUniform (const char* name, const int& count, const vec3* value) const;
		void setUniform (const char* name, const int& count, const vec4* value) const;
		void setUniform (const int& location, const int& count, const float* value) const;
		void setUniform (const int& location, const int& count, const vec2* value) const;
		void setUniform (const int& location, const int& count, const vec3* value) const;
		void setUniform (const int& location, const int& count, const vec4* value) const;

		void setUniformi (const char* name, const int& value) const;
		void setUniformi (const char* name, const int& x, const int& y) const;
		void setUniformi (const char* name, const ivec2& value) const;
		void setUniformi (const char* name, const int& x, const int& y, const int& z) const;
		void setUniformi (const char* name, const ivec3& value) const;
		void setUniformi (const char* name, const int& x, const int& y, const int& z, const int& w) const;
		void setUniformi (const char* name, const ivec4& value) const;
		void setUniformi (const int& location, const int& value) const;
		void setUniformi (const int& location, const ivec2& value) const;
		void setUniformi (const int& location, const ivec3& value) const;
		void setUniformi (const int& location, const ivec4& value) const;

		void setUniformi (const char* name, const int& count, const int* value) const;
		void setUniformi (const char* name, const int& count, const ivec2* value) const;
		void setUniformi (const char* name, const int& count, const ivec3* value) const;
		void setUniformi (const char* name, const int& count, const ivec4* value) const;
		void setUniformi (const int& location, const int& count, const int* value) const;
		void setUniformi (const int& location, const int& count, const ivec2* value) const;
		void setUniformi (const int& location, const int& count, const ivec3* value) const;
		void setUniformi (const int& location, const int& count, const ivec4* value) const;

		void setUniformui (const char* name, const uint& value) const;
		void setUniformui (const char* name, const uint& x, const uint& y) const;
		void setUniformui (const char* name, const uvec2& value) const;
		void setUniformui (const char* name, const uint& x, const uint& y, const uint& z) const;
		void setUniformui (const char* name, const uvec3& value) const;
		void setUniformui (const char* name, const uint& x, const uint& y, const uint& z, const uint& w) const;
		void setUniformui (const char* name, const uvec4& value) const;
		void setUniformui (const int& location, const uint& value) const;
		void setUniformui (const int& location, const uint& x, const uint& y) const;
		void setUniformui (const int& location, const uvec2& value) const;
		void setUniformui (const int& location, const uint& x, const uint& y, const uint& z) const;
		void setUniformui (const int& location, const uvec3& value) const;
		void setUniformui (const int& location, const uint& x, const uint& y, const uint& z, const uint& w) const;
		void setUniformui (const int& location, const uvec4& value) const;

		void setUniformui (const char* name, const int& count, const uint* value) const;
		void setUniformui (const char* name, const int& count, const uvec2* value) const;
		void setUniformui (const char* name, const int& count, const uvec3* value) const;
		void setUniformui (const char* name, const int& count, const uvec4* value) const;
		void setUniformui (const int& location, const int& count, const uint* value) const;
		void setUniformui (const int& location, const int& count, const uvec2* value) const;
		void setUniformui (const int& location, const int& count, const uvec3* value) const;
		void setUniformui (const int& location, const int& count, const uvec4* value) const;

		void setUniformd (const char* name, const double& value) const;
		void setUniformd (const char* name, const double& x, const double& y) const;
		void setUniformd (const char* name, const dvec2& value) const;
		void setUniformd (const char* name, const double& x, const double& y, const double& z) const;
		void setUniformd (const char* name, const dvec3& value) const;
		void setUniformd (const char* name, const double& x, const double& y, const double& z, const double& w) const;
		void setUniformd (const char* name, const dvec4& value) const;
		void setUniformd (const int& location, const double& value) const;
		void setUniformd (const int& location, const dvec2& value) const;
		void setUniformd (const int& location, const dvec3& value) const;
		void setUniformd (const int& location, const dvec4& value) const;

		void setUniformd (const char* name, const int& count, const double* value) const;
		void setUniformd (const char* name, const int& count, const dvec2* value) const;
		void setUniformd (const char* name, const int& count, const dvec3* value) const;
		void setUniformd (const char* name, const int& count, const dvec4* value) const;
		void setUniformd (const int& location, const int& count, const double* value) const;
		void setUniformd (const int& location, const int& count, const dvec2* value) const;
		void setUniformd (const int& location, const int& count, const dvec3* value) const;
		void setUniformd (const int& location, const int& count, const dvec4* value) const;

		void setUniformMat4 (const char* name, const mat4& value) const;
		void setUniformMat4 (const int& location, const mat4& value) const;
		void setUniformMat4 (const char* name, const int& count, const mat4* matrices) const;
		void setUniformMat4 (const int& location, const int& count, const mat4* matrices) const;
	};
	
}