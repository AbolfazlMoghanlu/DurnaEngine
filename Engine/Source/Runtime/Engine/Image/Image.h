#pragma once

namespace Durna
{
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

		unsigned char* Data = nullptr;

	private:
		
		std::string FilePath = "";
		int32 Width = 0;
		int32 Height = 0;
		uint32 NumberOfChannels = 0;
		bool bLoaded = false;
	};
}