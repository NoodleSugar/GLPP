#pragma once

#include "Texture.hpp"

#include <glad/glad.h>

namespace glpp::TextureFactory
{

Texture2D createColorTexture(int width, int height, unsigned char* data = nullptr);

Texture2D createAlphaColorTexture(int width, int height, unsigned char* data = nullptr);

Texture2D createDepthTexture(int width, int height);

Texture2D createStencilTexture(int width, int height);

Texture2D createDepthAndStencilTexture(int width, int height);

} // namespace glpp::TextureFactory
