#pragma once

namespace Durna
{
	struct VolumeGeometry
	{
		VolumeGeometry(std::wstring InName, std::wstring InPath)
			: Name(InName), Path(InPath)
		{ }

		std::wstring Name;
		std::wstring Path;
	};

	struct SystemFile
	{
		SystemFile(const std::wstring& InFullPath) 
		{
			FullPath = InFullPath;

			int32 LastSlash = FullPath.find_last_of(L"\\");
			Name = LastSlash >= 0 ? FullPath.substr(++LastSlash, FullPath.size() - LastSlash) : FullPath;

			int32 FirstDot = Name.find_first_of(L".");
			bDirectory = FirstDot < 0;
		}

		std::wstring Name;
		std::wstring FullPath;
		bool bDirectory;
	};
}