#pragma once

#include "Object.hpp"
#include "Texture.hpp"

namespace glpp
{

enum class FrameBufferTarget
{
	ReadAndDraw = GL_FRAMEBUFFER,
	Read		= GL_READ_FRAMEBUFFER,
	Draw		= GL_DRAW_FRAMEBUFFER
};

enum class FrameBufferAttachment
{
	Color			= GL_COLOR_ATTACHMENT0,
	Depth			= GL_DEPTH_ATTACHMENT,
	Stencil			= GL_STENCIL_ATTACHMENT,
	DepthAndStencil = GL_DEPTH_STENCIL_ATTACHMENT
};

enum class FrameBufferClearTarget
{
	Color			= GL_COLOR_BUFFER_BIT,
	Depth			= GL_DEPTH_BUFFER_BIT,
	Stencil			= GL_STENCIL_BUFFER_BIT,
	ColorAndDepth	= GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
	ColorAndStencil = GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
	DepthAndStencil = GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
	All				= GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT
};

class FrameBuffer : public Object
{
public:
	FrameBuffer() { glGenFramebuffers(1, &m_id); }

	~FrameBuffer() { glDeleteFramebuffers(1, &m_id); }

	void bind(FrameBufferTarget target = FrameBufferTarget::ReadAndDraw) { glBindFramebuffer((GLenum)target, m_id); }

	template<TextureTarget T>
	void attachTexture(FrameBufferTarget target, FrameBufferAttachment attachement, const Texture<T>& texture)
	{
		glFramebufferTexture2D((GLenum)target, (GLenum)attachement, (GLenum)T, texture.getId(), 0);
	}

	static void unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

	static void setClearColor(float r, float g, float b, float a) { glClearColor(r, g, b, a); }
	static void clear(FrameBufferClearTarget type) { glClear(static_cast<GLbitfield>(type)); }
};

} // namespace glpp