#include <GLPP/TextureFactory.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace glpp
{
Texture2D TextureFactory::fromFile(const char* filePath) noexcept(false)
{
	GLsizei		   width, height;
	unsigned char* data = stbi_load(filePath, &width, &height, nullptr, 0);

	if(!data)
		throw TextureLoadException(filePath);

	Texture2D texture(TextureInternalFormat::RGB,
					  PixelDataFormat::RGB,
					  PixelDataType::UnsignedByte,
					  width, height, data);

	stbi_image_free(data);

	return texture;
}

// TODO vérifier fonctionnement de ces méthodes avec les framebuffers...

Texture2D TextureFactory::createColorTexture(int width, int height)
{
	return Texture2D(
	 TextureInternalFormat::RGB,
	 PixelDataFormat::RGB,
	 PixelDataType::UnsignedByte,
	 width, height, nullptr, 0);
}

Texture2D TextureFactory::createDepthTexture(int width, int height)
{
	return Texture2D(
	 TextureInternalFormat::Depth,
	 PixelDataFormat::Depth,
	 PixelDataType::UnsignedByte,
	 width, height, nullptr, 0);
}

Texture2D TextureFactory::createStencilTexture(int width, int height)
{
	return Texture2D(
	 TextureInternalFormat::RGB,
	 PixelDataFormat::StencilIndex,
	 PixelDataType::UnsignedByte,
	 width, height, nullptr, 0);
}

Texture2D TextureFactory::createDepthAndStencilTexture(int width, int height)
{
	return Texture2D(
	 TextureInternalFormat::DepthStencil,
	 PixelDataFormat::DepthStencil,
	 PixelDataType::UnsignedInt24_8,
	 width, height, nullptr, 0);
}

} // namespace glpp