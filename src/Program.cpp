#include <GLPP/Program.hpp>

#include <glm/gtc/type_ptr.hpp>

namespace glpp
{
Program::Program(const VertexShader& vShader, const FragmentShader& fShader) noexcept(false) :
	Object(glCreateProgram())
{
	glAttachShader(m_id, vShader.getId());
	glAttachShader(m_id, fShader.getId());
	glLinkProgram(m_id);

	GLint success;
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if(!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(m_id, sizeof(infoLog), nullptr, infoLog);
		throw ProgramLinkException(infoLog);
	}
}

Program::~Program()
{
	if(m_id)
		glDeleteProgram(m_id);
}

void Program::use() const { glUseProgram(m_id); }

using namespace glm;

using fvec1 = glm::vec1;
using fvec2 = glm::vec2;
using fvec3 = glm::vec3;
using fvec4 = glm::vec4;

using uivec1 = glm::uvec1;
using uivec2 = glm::uvec2;
using uivec3 = glm::uvec3;
using uivec4 = glm::uvec4;

#define GET_UNIFORM_LOCATION GLint varLocation = glGetUniformLocation(m_id, name);

/**************************************
 * Define Program::setUniform methods *
 **************************************/

#define UNIFORM_PARAM_FORMAT(_n, _type) _type value##_n

#define UNIFORM_PARAM_LIST_1(_type) UNIFORM_PARAM_FORMAT(1, _type)
#define UNIFORM_PARAM_LIST_2(_type) UNIFORM_PARAM_LIST_1(_type), UNIFORM_PARAM_FORMAT(2, _type)
#define UNIFORM_PARAM_LIST_3(_type) UNIFORM_PARAM_LIST_2(_type), UNIFORM_PARAM_FORMAT(3, _type)
#define UNIFORM_PARAM_LIST_4(_type) UNIFORM_PARAM_LIST_3(_type), UNIFORM_PARAM_FORMAT(4, _type)

#define UNIFORM_ARG_FORMAT(_n) value##_n

#define UNIFORM_ARG_LIST_1 UNIFORM_ARG_FORMAT(1)
#define UNIFORM_ARG_LIST_2 UNIFORM_ARG_LIST_1, UNIFORM_ARG_FORMAT(2)
#define UNIFORM_ARG_LIST_3 UNIFORM_ARG_LIST_2, UNIFORM_ARG_FORMAT(3)
#define UNIFORM_ARG_LIST_4 UNIFORM_ARG_LIST_3, UNIFORM_ARG_FORMAT(4)

#define DEFINE_UNIFORM(_n, _type, _t)                                                \
	void Program::setUniform(const char* name, UNIFORM_PARAM_LIST_##_n(_type)) const \
	{                                                                                \
		GET_UNIFORM_LOCATION                                                         \
		glUniform##_n##_t(varLocation, UNIFORM_ARG_LIST_##_n);                       \
	}

#define DEFINE_UNIFORM_TYPE(_type, _t) \
	DEFINE_UNIFORM(1, _type, _t)       \
	DEFINE_UNIFORM(2, _type, _t)       \
	DEFINE_UNIFORM(3, _type, _t)       \
	DEFINE_UNIFORM(4, _type, _t)

#define DEFINE_ALL_UNIFORM          \
	DEFINE_UNIFORM_TYPE(GLfloat, f) \
	DEFINE_UNIFORM_TYPE(GLint, i)   \
	DEFINE_UNIFORM_TYPE(GLuint, ui)

DEFINE_ALL_UNIFORM

/*************************************************
 * Define Program::setUniformArray methods *
 *************************************************/

#define UNIFORM_ARR(_n, _t)                                                                    \
	void Program::setUniformArray(const char* name, const _t##vec##_n* value, int count) const \
	{                                                                                          \
		GET_UNIFORM_LOCATION                                                                   \
		glUniform##_n##_t##v(varLocation, count, &value->x);                                   \
	}

#define DEFINE_UNIFORM_ARR(_t) \
	UNIFORM_ARR(2, _t)         \
	UNIFORM_ARR(3, _t)         \
	UNIFORM_ARR(4, _t)

#define DEFINE_ALL_UNIFORM_ARR \
	DEFINE_UNIFORM_ARR(f)      \
	DEFINE_UNIFORM_ARR(i)      \
	DEFINE_UNIFORM_ARR(ui)

DEFINE_ALL_UNIFORM_ARR

/********************************************
 * Define Program::setUniformMatrix methods *
 ********************************************/

#define UNIFORM_MAT_CALL_X(_l, _c) glUniformMatrix##_l##x##_c##fv
#define UNIFORM_MAT_CALL(_l, _c)   glUniformMatrix##_l##fv

#define DEFINE_UNIFORM_MAT(_l, _c, _function)                                                                      \
	void Program::setUniformMatrix(const char* name, const mat##_l##x##_c* value, int count, bool transpose) const \
	{                                                                                                              \
		GET_UNIFORM_LOCATION                                                                                       \
		_function(_l, _c)(varLocation, count, transpose, value_ptr(*value));                                       \
	}

#define DEFINE_ALL_UNIFORM_MAT                   \
	DEFINE_UNIFORM_MAT(2, 2, UNIFORM_MAT_CALL)   \
	DEFINE_UNIFORM_MAT(2, 3, UNIFORM_MAT_CALL_X) \
	DEFINE_UNIFORM_MAT(2, 4, UNIFORM_MAT_CALL_X) \
	DEFINE_UNIFORM_MAT(3, 2, UNIFORM_MAT_CALL_X) \
	DEFINE_UNIFORM_MAT(3, 3, UNIFORM_MAT_CALL)   \
	DEFINE_UNIFORM_MAT(3, 4, UNIFORM_MAT_CALL_X) \
	DEFINE_UNIFORM_MAT(4, 2, UNIFORM_MAT_CALL_X) \
	DEFINE_UNIFORM_MAT(4, 3, UNIFORM_MAT_CALL_X) \
	DEFINE_UNIFORM_MAT(4, 4, UNIFORM_MAT_CALL)

DEFINE_ALL_UNIFORM_MAT

} // namespace glpp
