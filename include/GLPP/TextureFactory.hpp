#pragma once

#include "Texture.hpp"

#include <glad/glad.h>

namespace glpp
{
class TextureFactory
{
public:
	static Texture2D fromFile(const char* filePath) noexcept(false);

	static Texture2D createColorTexture(int width, int height);

	static Texture2D createDepthTexture(int width, int height);

	static Texture2D createStencilTexture(int width, int height);

	static Texture2D createDepthAndStencilTexture(int width, int height);
};

} // namespace glpp
