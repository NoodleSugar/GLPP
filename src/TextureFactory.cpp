#include <GLPP/TextureFactory.hpp>

namespace glpp::TextureFactory
{

// TODO vérifier fonctionnement de ces méthodes avec les framebuffers...

Texture2D createColorTexture(int width, int height, unsigned char* data)
{
	return Texture2D(
	 TextureInternalFormat::RGB,
	 PixelDataFormat::RGB,
	 PixelDataType::UnsignedByte,
	 width, height, data, 0);
}

Texture2D createAlphaColorTexture(int width, int height, unsigned char* data)
{
	return Texture2D(
	 TextureInternalFormat::RGBA,
	 PixelDataFormat::RGBA,
	 PixelDataType::UnsignedByte,
	 width, height, data, 0);
}

Texture2D createDepthTexture(int width, int height)
{
	return Texture2D(
	 TextureInternalFormat::Depth,
	 PixelDataFormat::Depth,
	 PixelDataType::UnsignedByte,
	 width, height, nullptr, 0);
}

Texture2D createStencilTexture(int width, int height)
{
	return Texture2D(
	 TextureInternalFormat::RGB,
	 PixelDataFormat::StencilIndex,
	 PixelDataType::UnsignedByte,
	 width, height, nullptr, 0);
}

Texture2D createDepthAndStencilTexture(int width, int height)
{
	return Texture2D(
	 TextureInternalFormat::DepthStencil,
	 PixelDataFormat::DepthStencil,
	 PixelDataType::UnsignedInt24_8,
	 width, height, nullptr, 0);
}

} // namespace glpp::TextureFactory