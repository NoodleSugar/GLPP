#pragma once

#include <glad/glad.h>

namespace glpp
{

enum class CullMode
{
	Front		 = GL_FRONT,
	Back		 = GL_BACK,
	FrontAndBack = GL_FRONT_AND_BACK
};

enum class SFactor
{
	Zero			 = GL_ZERO,
	One				 = GL_ONE,
	DstColor		 = GL_DST_COLOR,
	OneMinusDstColor = GL_ONE_MINUS_DST_COLOR,
	SrcAlpha		 = GL_SRC_ALPHA,
	OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
	DstAlpha		 = GL_DST_ALPHA,
	OneMinusDstAlpha = GL_ONE_MINUS_DST_ALPHA,
	SrcAlphaSaturate = GL_SRC_ALPHA_SATURATE
};

enum class DFactor
{
	Zero			 = GL_ZERO,
	One				 = GL_ONE,
	SrcColor		 = GL_SRC_COLOR,
	OneMinusSrcColor = GL_ONE_MINUS_SRC_COLOR,
	SrcAlpha		 = GL_SRC_ALPHA,
	OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
	DstAlpha		 = GL_DST_ALPHA,
	OneMinusDstAlpha = GL_ONE_MINUS_DST_ALPHA
};

inline void setViewport(GLint x, GLint y, GLsizei w, GLsizei h) { glViewport(x, y, w, h); }
inline void setScissor(GLint x, GLint y, GLsizei w, GLsizei h) { glScissor(x, y, w, h); }
inline void setCullMode(CullMode mode) { glCullFace(static_cast<GLenum>(mode)); }
inline void setBlendFunc(SFactor s, DFactor d) { glBlendFunc(static_cast<GLenum>(s), static_cast<GLenum>(d)); }

} // namespace glpp
