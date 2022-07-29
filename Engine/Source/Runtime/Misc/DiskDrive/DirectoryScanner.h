#pragma once
 
#include "Runtime/Misc/DiskDrive/DiskDriveTypes.h"
#include "Runtime/Misc/DiskDrive/DiskDriveHelpers.h"

namespace Durna
{
	class DirectoryScanner
	{
	public:
		static void GetFileInPath(const std::wstring& Path, std::vector<SystemFile>& OutFiles);
	};
}

