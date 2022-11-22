#pragma once

#include <glad/glad.h>

namespace glpp
{
class Object
{
public:
	constexpr Object() :
		m_id(0) {}
	Object(const Object&) = delete;
	constexpr Object(Object&& other) :
		m_id(other.m_id) { other.m_id = 0; };

	constexpr explicit Object(GLuint id) :
		m_id(id) {}

	virtual ~Object() {}

	constexpr Object& operator=(Object&& other)
	{
		m_id	   = other.m_id;
		other.m_id = 0;
		return *this;
	}

	constexpr GLuint getId() const { return m_id; }

protected:
	GLuint m_id;
};

} // namespace glpp