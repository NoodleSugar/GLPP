#pragma once

#include "Object.hpp"

namespace glpp
{

enum class BufferType
{
	VertexArray	 = GL_ARRAY_BUFFER,
	ElementArray = GL_ELEMENT_ARRAY_BUFFER,
	Uniform		 = GL_UNIFORM_BUFFER
};

enum class BufferUsage
{
	StreamDraw	= GL_STREAM_DRAW,
	StreamRead	= GL_STREAM_READ,
	StreamCopy	= GL_STREAM_COPY,
	StaticDraw	= GL_STATIC_DRAW,
	StaticRead	= GL_STATIC_READ,
	StaticCopy	= GL_STATIC_COPY,
	DynamicDraw = GL_DYNAMIC_DRAW,
	DynamicRead = GL_DYNAMIC_READ,
	DynamicCopy = GL_DYNAMIC_COPY
};

template<BufferType T>
class Buffer : public Object
{
public:
	Buffer();
	Buffer(const Buffer&) = delete;
	Buffer(Buffer&&)	  = default;

	Buffer& operator=(const Buffer&) = delete;
	Buffer& operator=(Buffer&&)		 = default;

	~Buffer();

	void bind() const;

	void setData(const void* data, size_t size, BufferUsage);
	void setSubData(const void* data, size_t offset, size_t size);

	void bindBufferBase(unsigned int index) const;
	void bindBufferRange(unsigned int index, size_t offset, size_t size) const;

	static void unbind();

private:
	static constexpr GLenum BUFFER_TYPE = static_cast<GLenum>(T);
};

using VertexBuffer	= Buffer<BufferType::VertexArray>;
using ElementBuffer = Buffer<BufferType::ElementArray>;
using UniformBuffer = Buffer<BufferType::Uniform>;

template<BufferType T>
inline Buffer<T>::Buffer()
{
	glGenBuffers(1, &m_id);
}

template<BufferType T>
inline Buffer<T>::~Buffer()
{
	if(m_id)
		glDeleteBuffers(1, &m_id);
}

template<BufferType T>
inline void Buffer<T>::bind() const
{
	glBindBuffer(BUFFER_TYPE, m_id);
}

template<BufferType T>
inline void Buffer<T>::setData(const void* data, size_t size, BufferUsage usage)
{
	bind();
	glBufferData(BUFFER_TYPE, size, data, (GLenum)usage);
	unbind();
}

template<BufferType T>
inline void Buffer<T>::setSubData(const void* data, size_t offset, size_t size)
{
	bind();
	glBufferSubData(BUFFER_TYPE, offset, size, data);
	unbind();
}

template<BufferType T>
inline void Buffer<T>::bindBufferBase(unsigned int index) const
{
	glBindBufferBase(BUFFER_TYPE, index, m_id);
}

template<BufferType T>
inline void Buffer<T>::bindBufferRange(unsigned int index, size_t offset, size_t size) const
{
	glBindBufferRange(BUFFER_TYPE, index, m_id, offset, size);
}

template<BufferType T>
inline void Buffer<T>::unbind()
{
	glBindBuffer(BUFFER_TYPE, 0);
}

} // namespace glpp