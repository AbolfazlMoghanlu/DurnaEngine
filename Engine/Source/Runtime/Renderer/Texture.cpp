#include "DurnaPCH.h"
#include "Texture.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"

LOG_DEFINE_CATEGORY(LogTexture, "Texture")

namespace Durna
{
	Texture::Texture()
	{
		glGenTextures(1, &ID);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &ID);
	}

	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, ID);
	}

	void Texture::UnBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::ActivateTexture(uint8 Index)
	{
		glActiveTexture(GetGLTextureSlot(Index));
	}

	uint32 Texture::GetGLTextureSlot(uint8 Index)
	{
		return GL_TEXTURE0 + Index;
	}
}