#pragma once

#include "Object.hpp"

#include <exception>
#include <string>

namespace glpp
{
enum class TextureTarget
{
	Texture2D			  = GL_TEXTURE_2D,
	ProxyTexture2D		  = GL_PROXY_TEXTURE_2D,
	Texture1DArray		  = GL_TEXTURE_1D_ARRAY,
	ProxyTexture1DArray	  = GL_PROXY_TEXTURE_1D_ARRAY,
	TextureRectangle	  = GL_TEXTURE_RECTANGLE,
	ProxyTextureRectangle = GL_PROXY_TEXTURE_RECTANGLE,
	CubeMapPositiveX	  = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	CubeMapNegativeX	  = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	CubeMapPositiveY	  = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	CubeMapNegativeY	  = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	CubeMapPositiveZ	  = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	CubeMapNegativeZ	  = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
	ProxyCubeMap		  = GL_PROXY_TEXTURE_CUBE_MAP
};

enum class TextureInternalFormat
{
	Depth		 = GL_DEPTH_COMPONENT,
	DepthStencil = GL_DEPTH_STENCIL,
	// TODO a voir Depth24Stencil8 = GL_DEPTH24_STENCIL8,
	Red	 = GL_RED,
	RG	 = GL_RG,
	RGB	 = GL_RGB,
	RGBA = GL_RGBA
};

enum class PixelDataFormat
{
	Red			 = GL_RED,
	RG			 = GL_RG,
	RGB			 = GL_RGB,
	BGR			 = GL_BGR,
	RGBA		 = GL_RGBA,
	BGRA		 = GL_BGRA,
	RedInteger	 = GL_RED_INTEGER,
	RGInteger	 = GL_RG_INTEGER,
	RGBInteger	 = GL_RGB_INTEGER,
	BGRInteger	 = GL_BGR_INTEGER,
	RGBAInteger	 = GL_RGBA_INTEGER,
	BGRAInteger	 = GL_BGRA_INTEGER,
	StencilIndex = GL_STENCIL_INDEX,
	Depth		 = GL_DEPTH_COMPONENT,
	DepthStencil = GL_DEPTH_STENCIL
};

enum class PixelDataType
{
	UnsignedByte			 = GL_UNSIGNED_BYTE,
	Byte					 = GL_BYTE,
	UnsignedShort			 = GL_UNSIGNED_SHORT,
	Short					 = GL_SHORT,
	UnsignedInt				 = GL_UNSIGNED_INT,
	Int						 = GL_INT,
	HalfFloat				 = GL_HALF_FLOAT,
	Float					 = GL_FLOAT,
	UnsignedByte3_3_2		 = GL_UNSIGNED_BYTE_3_3_2,
	UnsignedByte2_3_3Rev	 = GL_UNSIGNED_BYTE_2_3_3_REV,
	UnsignedShort5_6_5		 = GL_UNSIGNED_SHORT_5_6_5,
	UnsignedShort5_6_5Rev	 = GL_UNSIGNED_SHORT_5_6_5_REV,
	UnsignedShort4_4_4_4	 = GL_UNSIGNED_SHORT_4_4_4_4,
	UnsignedShort4_4_4_4Rev	 = GL_UNSIGNED_SHORT_4_4_4_4_REV,
	UnsignedShort5_5_5_1	 = GL_UNSIGNED_SHORT_5_5_5_1,
	UnsignedShort1_5_5_5Rev	 = GL_UNSIGNED_SHORT_1_5_5_5_REV,
	UnsignedInt8_8_8_8		 = GL_UNSIGNED_INT_8_8_8_8,
	UnsignedInt8_8_8_8Rev	 = GL_UNSIGNED_INT_8_8_8_8_REV,
	UnsignedInt10_10_10_2	 = GL_UNSIGNED_INT_10_10_10_2,
	UnsignedInt10_10_10_2Rev = GL_UNSIGNED_INT_2_10_10_10_REV,
	UnsignedInt24_8			 = GL_UNSIGNED_INT_24_8
};

class TextureLoadException : public std::exception
{
public:
	explicit TextureLoadException(const char* filePath) :
		m_filePath(filePath) {}
	~TextureLoadException() noexcept = default;

	const char* what() const noexcept override
	{
		return (std::string("Failed to load : ") + m_filePath).c_str();
	}

private:
	std::string m_filePath;
};

// TODO Faire classe template avec TextureTarget
template<TextureTarget T>
class Texture : public Object
{
public:
	Texture()				= delete;
	Texture(const Texture&) = delete;
	Texture(Texture&&)		= default;

	/**
	 * If TextureTarget is TextureRectangle or ProxyTextureRectangle, levelOfDetail must be 0
	 */
	Texture(TextureInternalFormat,
			PixelDataFormat,
			PixelDataType,
			int			width,
			int			height,
			const void* data,
			int			levelOfDetail = 0);

	~Texture();

	Texture& operator=(Texture&&) = default;

	void bind() const;

	static void unbind();

	static Texture fromFile(const char*) noexcept(false);
	static Texture createColorTexture(int width, int height);
	static Texture createDepthTexture(int width, int height);
	static Texture createStencilTexture(int width, int height);
	static Texture createDepthAndStencilTexture(int width, int height);

private:
	static constexpr GLenum TEXTURE_TARGET = (GLenum)T;
};

using Texture2D = Texture<TextureTarget::Texture2D>;

template<TextureTarget T>
Texture<T>::Texture(TextureInternalFormat internalformat,
					PixelDataFormat		  pixelFormat,
					PixelDataType		  pixelType,
					int					  width,
					int					  height,
					const void*			  data,
					int					  levelOfDetail)
{
	glGenTextures(1, &m_id);
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(TEXTURE_TARGET, levelOfDetail, (int)internalformat, width, height, 0, (GLenum)pixelFormat, (GLenum)pixelType, data);
	// TODO glGenerateMipmap(GL_TEXTURE_2D);
	unbind();
}

template<TextureTarget T>
Texture<T>::~Texture()
{
	if(m_id)
		glDeleteTextures(1, &m_id);
}

template<TextureTarget T>
void Texture<T>::bind() const
{
	glBindTexture(TEXTURE_TARGET, m_id);
}

template<TextureTarget T>
void Texture<T>::unbind()
{
	glBindTexture(TEXTURE_TARGET, 0);
}

} // namespace glpp