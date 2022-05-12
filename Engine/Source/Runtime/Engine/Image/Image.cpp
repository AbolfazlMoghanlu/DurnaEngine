#include "DurnaPCH.h"
#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "ThirdParty/Stb/stb_image.h"

LOG_DEFINE_CATEGORY(LogImage, "Image")

namespace Durna
{
	Image::Image()
	{}

	Image::Image(const char* InPath, bool bLoad)
		: FilePath(InPath)
	{
		if (bLoad)
		{
			Load();
		}
	}

	Image::~Image()
	{
		Unload();
	}

	bool Image::Load()
	{
		if (IsLoaded())
		{
			return true;
		}

		unsigned char* Result;
		int32 ImageWidth, ImageHeight, ImageNumberOfChannels;

 		Result = stbi_load(FilePath.c_str(),
 			&ImageWidth, &ImageHeight, &ImageNumberOfChannels, 0);

		if (Result)
		{
			ReleaseResources();

			Data = Result;
			Width = ImageWidth;
			Height = ImageHeight;
			NumberOfChannels = ImageNumberOfChannels;
			
			MarkLoaded();
		}

		else
		{
			const char* res = stbi_failure_reason();
			LOG(LogImage, Error, "Failed to load \"%s\".\n%s", FilePath.c_str(), res);
		}

		return IsLoaded();
	}

	void Image::Unload()
	{
		ReleaseResources();
		MarkUnloaded();
	}

	int32 Image::GetWidth() const
	{
		return Width;
	}

	int32 Image::GetHeight() const
	{
		return Height;
	}

	uint32 Image::GetNumberOfChannels() const
	{
		return NumberOfChannels;
	}

	uint32 Image::GetFormat() const
	{
		switch (NumberOfChannels)
		{
		case 1:
			return static_cast<uint32>(EImageFormat::R8);
		case 2:
			return static_cast<uint32>(EImageFormat::RG8);
		case 3:
			return static_cast<uint32>(EImageFormat::RGB8);
		case 4:
			return static_cast<uint32>(EImageFormat::RGBA8);

		default:
			return 0;
		}
	}

	bool Image::IsLoaded() const
	{
		return bLoaded;
	}

	void Image::MarkLoaded()
	{
		bLoaded = true;
	}

	void Image::MarkUnloaded()
	{
		bLoaded = false;
	}

	void Image::ReleaseResources()
	{
		if (Data)
		{
			stbi_image_free(Data);
		}
	}

	

}