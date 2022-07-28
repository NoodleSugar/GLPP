#pragma once

#include <glad/glad.h>

namespace glpp
{
class Object
{
public:
	Object()			  = default;
	Object(const Object&) = delete;
	Object(Object&& other) :
		m_id(other.m_id) { other.m_id = 0; };

	explicit Object(GLuint id) :
		m_id(id) {}

	virtual ~Object() {}

	Object& operator=(Object&& other)
	{
		m_id	   = other.m_id;
		other.m_id = 0;
		return *this;
	}

	GLuint getId() const { return m_id; }

protected:
	GLuint m_id;
};

} // namespace glpp