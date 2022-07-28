#include <GLPP/VertexArray.hpp>

namespace glpp
{

VertexArray::VertexArray() { glGenVertexArrays(1, &m_id); }

VertexArray::~VertexArray()
{
	if(m_id)
		glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind() const { glBindVertexArray(m_id); }

void VertexArray::configureVertexAttributes(const VertexAttributesConfiguration& config) const
{
	glVertexAttribPointer(config.index, config.vertexSize, (GLenum)config.type, config.normalized, config.stride, config.offset);
	glEnableVertexAttribArray(config.index);
}

void VertexArray::unbind() { glBindVertexArray(0); }

} // namespace glpp
