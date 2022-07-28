#pragma once

#include "Object.hpp"

#include <glad/glad.h>

#include <exception>
#include <fstream>
#include <sstream>
#include <string>

namespace glpp
{

enum class ShaderType
{
	Vertex	 = GL_VERTEX_SHADER,
	Fragment = GL_FRAGMENT_SHADER
};

class ShaderCompileException : public std::exception
{
public:
	explicit ShaderCompileException(const char* msg) :
		m_infoLog(msg) {}
	~ShaderCompileException() noexcept = default;

	const char* what() const noexcept override { return m_infoLog.c_str(); }

private:
	std::string m_infoLog;
};

template<ShaderType T>
class Shader : public Object
{
public:
	Shader()			  = delete;
	Shader(const Shader&) = delete;
	Shader(Shader&&)	  = default;

	Shader(const char*) noexcept(false);

	~Shader();

	static Shader fromFile(const char*) noexcept(false);

private:
	static constexpr GLenum SHADER_TYPE = static_cast<GLenum>(T);
};

using VertexShader	 = Shader<ShaderType::Vertex>;
using FragmentShader = Shader<ShaderType::Fragment>;

template<ShaderType T>
Shader<T>::Shader(const GLchar* source) noexcept(false) :
	Object(glCreateShader(SHADER_TYPE))
{
	glShaderSource(m_id, 1, &source, nullptr);
	glCompileShader(m_id);

	GLint success;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(m_id, sizeof(infoLog), nullptr, infoLog);
		throw ShaderCompileException(infoLog);
	}
}

template<ShaderType T>
Shader<T>::~Shader()
{
	if(m_id)
		glDeleteShader(m_id);
}

template<ShaderType T>
Shader<T> Shader<T>::fromFile(const char* filePath) noexcept(false)
{
	std::ifstream fileStream(filePath, std::ios::ate);
	auto		  fileLength = fileStream.tellg();

	std::string source(fileLength, '\0');

	fileStream.seekg(0, std::ios::beg);
	fileStream.read(source.data(), fileLength);
	fileStream.close();

	return Shader(source.c_str());
}

} // namespace glpp