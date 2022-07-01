#include "DurnaPCH.h"
#include "Texture2D.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"

LOG_DEFINE_CATEGORY(LogTexture2D, "Texture2D")

namespace Durna
{
	Texture2D::Texture2D(Image* Img) : Texture()
	{
		SetSource(Img);
	}

	void Texture2D::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, ID);
	}

	void Texture2D::UpdateTexture()
	{
		if (IsDirty() && SourceImage && SourceImage->Load())
		{
			glTexImage2D(GL_TEXTURE_2D, 0, static_cast<uint32>(InternalFormat)
				, SourceImage->GetWidth(), SourceImage->GetHeight(), 0, SourceImage->GetFormat(), GL_UNSIGNED_BYTE, SourceImage->Data);

			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<uint32>(SourceImage->X_Wrap));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<uint32>(SourceImage->Y_Wrap));

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<uint32>(SourceImage->X_Filter));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<uint32>(SourceImage->Y_Filter));

			bDirtyFlag = false;
		}
	}

	void Texture2D::SetSource(Image* Img)
	{
		SourceImage = Img;
		MarkDirty();
	}

	Image* Texture2D::GetSource() const
	{
		return SourceImage;
	}

	bool Texture2D::IsDirty() const
	{
		return bDirtyFlag;
	}

	void Texture2D::MarkDirty()
	{
		bDirtyFlag = true;
	}
}