#include "DurnaPCH.h"
#include "Texture.h"
#include "Runtime/Engine/Image/Image.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"

LOG_DEFINE_CATEGORY(LogTexture, "Texture")

namespace Durna
{
	Texture::Texture(Image* Img) 
	{
		glGenTextures(1, &ID);
		SetSource(Img);
	}

	Texture::Texture() : Texture(nullptr)
	{}

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

	void Texture::UpdateTexture()
	{
		if (IsDirty() && SourceImage && SourceImage->Load())
		{
			glTexImage2D(GL_TEXTURE_2D, 0, static_cast<uint32>(SourceImage->Format)
				, SourceImage->GetWidth(), SourceImage->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, SourceImage->Data);

			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<uint32>(SourceImage->X_Wrap));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<uint32>(SourceImage->Y_Wrap));

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<uint32>(SourceImage->X_Filter));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<uint32>(SourceImage->Y_Filter));

			bDirtyFlag = false;
		}
	}

	void Texture::SetSource(Image* Img)
	{
		SourceImage = Img;
		MarkDirty();
	}

	Image* Texture::GetSource() const
	{
		return SourceImage;
	}

	bool Texture::IsDirty() const
	{
		return bDirtyFlag;
	}

	void Texture::MarkDirty()
	{
		bDirtyFlag = true;
	}

}