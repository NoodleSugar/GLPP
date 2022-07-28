#pragma once

#include "Object.hpp"
#include "Shader.hpp"

#include <glad/glad.h>
#include <glm/matrix.hpp>

#include <exception>
#include <string_view>

namespace glpp
{

#define GLPP_DECLARE_SET_UNIFORM_1(_type) void setUniform(const char*, _type) const;
#define GLPP_DECLARE_SET_UNIFORM_2(_type) void setUniform(const char*, _type, _type) const;
#define GLPP_DECLARE_SET_UNIFORM_3(_type) void setUniform(const char*, _type, _type, _type) const;
#define GLPP_DECLARE_SET_UNIFORM_4(_type) void setUniform(const char*, _type, _type, _type, _type) const;

#define GLPP_DECLARE_SET_UNIFORM_ALL(_type) \
	GLPP_DECLARE_SET_UNIFORM_1(_type)       \
	GLPP_DECLARE_SET_UNIFORM_2(_type)       \
	GLPP_DECLARE_SET_UNIFORM_3(_type)       \
	GLPP_DECLARE_SET_UNIFORM_4(_type)

#define GLPP_DECLARE_SET_UNIFORM_ARRAY(_type, _n) \
	void setUniformArray(const char*, const glm::_type##_n*, int count = 1) const;

#define GLPP_DECLARE_SET_UNIFORM_ARRAY_ALL(_type) \
	GLPP_DECLARE_SET_UNIFORM_ARRAY(_type, 2)      \
	GLPP_DECLARE_SET_UNIFORM_ARRAY(_type, 3)      \
	GLPP_DECLARE_SET_UNIFORM_ARRAY(_type, 4)

#define GLPP_DECLARE_SET_UNIFORM_MATRIX(_l, _c) \
	void setUniformMatrix(const char*, const glm::mat##_l##x##_c*, int count = 1, bool transpose = false) const;

#define GLPP_DECLARE_SET_UNIFORM_MATRIX_ALL(_l) \
	GLPP_DECLARE_SET_UNIFORM_MATRIX(_l, 2)      \
	GLPP_DECLARE_SET_UNIFORM_MATRIX(_l, 3)      \
	GLPP_DECLARE_SET_UNIFORM_MATRIX(_l, 4)

class ProgramLinkException : public std::exception
{
public:
	explicit ProgramLinkException(const char* msg) :
		m_infoLog(msg) {}
	~ProgramLinkException() noexcept = default;

	virtual const char* what() const noexcept override { return m_infoLog.c_str(); }

private:
	std::string m_infoLog;
};

class Program : public Object
{
public:
	Program()				= delete;
	Program(const Program&) = delete;
	Program(Program&&)		= default;

	Program& operator=(const Program&) = delete;
	Program& operator=(Program&&)	   = default;

	Program(const VertexShader&, const FragmentShader&) noexcept(false);

	~Program();

	GLPP_DECLARE_SET_UNIFORM_ALL(GLfloat)
	GLPP_DECLARE_SET_UNIFORM_ALL(GLint)
	GLPP_DECLARE_SET_UNIFORM_ALL(GLuint)

	GLPP_DECLARE_SET_UNIFORM_ARRAY_ALL(vec)
	GLPP_DECLARE_SET_UNIFORM_ARRAY_ALL(ivec)
	GLPP_DECLARE_SET_UNIFORM_ARRAY_ALL(uvec)

	GLPP_DECLARE_SET_UNIFORM_MATRIX_ALL(2)
	GLPP_DECLARE_SET_UNIFORM_MATRIX_ALL(3)
	GLPP_DECLARE_SET_UNIFORM_MATRIX_ALL(4)

	void use() const;
};

#undef GLPP_DECLARE_SET_UNIFORM_1
#undef GLPP_DECLARE_SET_UNIFORM_2
#undef GLPP_DECLARE_SET_UNIFORM_3
#undef GLPP_DECLARE_SET_UNIFORM_4
#undef GLPP_DECLARE_SET_UNIFORM_ALL

#undef GLPP_DECLARE_SET_UNIFORM_ARRAY
#undef GLPP_DECLARE_SET_UNIFORM_ARRAY_ALL

#undef GLPP_DECLARE_SET_UNIFORM_MATRIX
#undef GLPP_DECLARE_SET_UNIFORM_MATRIX_ALL

} // namespace glpp