#pragma once

namespace Durna
{
	enum class EImageFormat : uint32
	{
		R8		= 0x2002,
		RG8		= 0x8227,
		RGB8	= 0x1907,
		RGBA8	= 0x1908
	};

	enum class EImageWrap : uint32
	{
		Repeat			= 0x2901,
		MirroredRepeat	= 0x8370,
		ClampToEdge		= 0x812F,
		ClampToBorder	= 0x812D
	};

	enum class EImageFilter : uint32
	{
		Nearest			= 0x2600,
		Linear			= 0x2601,
		MipmapNearest	= 0x2700,
		MipmapLinear	= 0x2702
	};
	

	class Image
	{
	public:
		Image();
		Image(const char* InPath, bool bLoad = true);

		~Image();

		bool Load();
		void Unload();

		int32 GetWidth() const;
		int32 GetHeight() const;
		uint32 GetNumberOfChannels() const;

		bool IsLoaded() const;
		void MarkLoaded();
		void MarkUnloaded();
		void ReleaseResources();


		unsigned char* Data = nullptr;
		EImageFormat Format		= EImageFormat::RGB8;
		EImageWrap X_Wrap		= EImageWrap::Repeat;
		EImageWrap Y_Wrap		= EImageWrap::Repeat;
		EImageFilter X_Filter	= EImageFilter::Linear;
		EImageFilter Y_Filter	= EImageFilter::Linear;

	private:
		
		std::string FilePath = "";
		int32 Width = 0;
		int32 Height = 0;
		uint32 NumberOfChannels = 0;
		bool bLoaded = false;
	};
}