#include "DurnaPCH.h"
#include "TextureCube.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"

LOG_DEFINE_CATEGORY(LogTextureCube, "TextureCube")

namespace Durna
{
	TextureCube::TextureCube(Image* InTopImage, Image* InBottomImage, Image* InRightImage,
		Image* InLeftImage, Image* InFrontImage, Image* InBackImage) : Texture()
	{
		SetSources(InTopImage, InBottomImage, InRightImage, InLeftImage, InFrontImage, InBackImage);
	}

	TextureCube::TextureCube() : TextureCube(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr)
	{ }

	TextureCube::~TextureCube()
	{ }

	void TextureCube::Bind() const
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
	}

	void TextureCube::UpdateTexture()
	{
		if (IsDirty())
		{
			auto LoadCubemapFace = [&](ECubemapFace CubemapFace, Image* SourceImage)
			{
				if (SourceImage && SourceImage->Load())
				{
					glTexImage2D(static_cast<uint32>(CubemapFace), 0, static_cast<uint32>(InternalFormat)
						, SourceImage->GetWidth(), SourceImage->GetHeight(), 0, SourceImage->GetFormat(),
						GL_UNSIGNED_BYTE, SourceImage->Data);
				}
				else
				{
					LOG(LogTextureCube, Error, "Failed to create cube map face.");
				}
			};

			LoadCubemapFace(ECubemapFace::Top,		TopImage);
			LoadCubemapFace(ECubemapFace::Bottom,	BottomImage);
			LoadCubemapFace(ECubemapFace::Right,	RightImage);
			LoadCubemapFace(ECubemapFace::Left,		LeftImage);
			LoadCubemapFace(ECubemapFace::Front,	FrontImage);
			LoadCubemapFace(ECubemapFace::Back,		BackImage);

			//glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

			bDirtyFlag = false;
		}
	}

	void TextureCube::SetSources(Image* InTopImage, Image* InBottomImage, Image* InRightImage, Image* InLeftImage, Image* InFrontImage, Image* InBackImage)
	{
		TopImage	= InTopImage;
		BottomImage = InBottomImage;
		RightImage	= InRightImage;
		LeftImage	= InLeftImage;
		FrontImage	= InFrontImage;
		BackImage	= InBackImage;

		MarkDirty();
	}

	bool TextureCube::IsDirty() const
	{
		return bDirtyFlag;
	}

	void TextureCube::MarkDirty()
	{
		bDirtyFlag = true;
	}
}