#pragma once

#include "Object.hpp"

#include <glad/glad.h>

namespace glpp
{
enum class AttributeType
{
	Byte		  = GL_BYTE,
	UnsignedByte  = GL_UNSIGNED_BYTE,
	Short		  = GL_SHORT,
	UnsignedShort = GL_UNSIGNED_SHORT,
	Int			  = GL_INT,
	UnsignedInt	  = GL_UNSIGNED_INT,
	HalfFloat	  = GL_HALF_FLOAT,
	Float		  = GL_FLOAT,
	Double		  = GL_DOUBLE
};

struct VertexAttributesConfiguration
{
	int			  index;
	int			  vertexSize;
	AttributeType type;
	bool		  normalized;
	int			  stride;
	void*		  offset;
};

class VertexArray : public Object
{
public:
	VertexArray();
	VertexArray(const VertexArray&) = delete;
	VertexArray(VertexArray&&)		= default;

	~VertexArray();

	void bind() const;

	void configureVertexAttributes(const VertexAttributesConfiguration&) const;

	static void unbind();
};

} // namespace glpp