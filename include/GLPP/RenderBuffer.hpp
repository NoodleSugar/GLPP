#pragma once

#include "Object.hpp"

namespace glpp
{

class RenderBuffer : public Object
{
public:
	RenderBuffer() { glGenRenderbuffers(1, &m_id); }

	RenderBuffer(const RenderBuffer&) = delete;
	RenderBuffer(RenderBuffer&&)	  = default;

	RenderBuffer& operator=(const RenderBuffer&) = delete;
	RenderBuffer& operator=(RenderBuffer&&)		 = default;

	void bind() { glBindRenderbuffer(GL_RENDERBUFFER, m_id); }

	static void unbind() { glBindRenderbuffer(GL_RENDERBUFFER, 0); }
};

} // namespace glpp