#pragma once

#include <glad/glad.h>

namespace glpp::Drawer
{

enum class DrawMode
{
	Points				  = GL_POINTS,
	LineStrip			  = GL_LINE_STRIP,
	LineLoop			  = GL_LINE_LOOP,
	Lines				  = GL_LINES,
	LineStripAdjacency	  = GL_LINE_STRIP_ADJACENCY,
	LinesAdjacency		  = GL_LINES_ADJACENCY,
	TriangleStrip		  = GL_TRIANGLE_STRIP,
	TriangleFan			  = GL_TRIANGLE_FAN,
	Triangles			  = GL_TRIANGLES,
	TriangleStipAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
	TriangleAdjacency	  = GL_TRIANGLES_ADJACENCY,
	Patches				  = GL_PATCHES
};

enum class IndiceType
{
	UnsignedByte  = GL_UNSIGNED_BYTE,
	UnsignedShort = GL_UNSIGNED_SHORT,
	UnsignedInt	  = GL_UNSIGNED_INT
};

enum class PolygonFace
{
	Front		 = GL_FRONT,
	Back		 = GL_BACK,
	FrontAndBack = GL_FRONT_AND_BACK
};

enum class PolygonMode
{
	Point = GL_POINT,
	Line  = GL_LINE,
	Fill  = GL_FILL
};

inline void drawArrays(DrawMode mode, int first, int count) { glDrawArrays((GLenum)mode, first, count); }
inline void drawArraysInstanced() {}
inline void drawElements(DrawMode mode, IndiceType type, int count) { glDrawElements((GLenum)mode, count, (GLenum)type, 0); }
inline void drawElementsInstanced() {}
inline void setPolygonMode(PolygonFace face, PolygonMode mode) { glPolygonMode((GLenum)face, (GLenum)mode); }

} // namespace glpp::Drawer