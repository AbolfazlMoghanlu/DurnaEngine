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
			// TODO: make custom data structure to avoid coppying inline data to std::vector
			Data.assign((size_t)ImageWidth * (size_t)ImageHeight, *Result);
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
}