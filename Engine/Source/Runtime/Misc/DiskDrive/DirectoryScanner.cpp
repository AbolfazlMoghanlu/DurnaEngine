#include "DurnaPCH.h"
#include "DirectoryScanner.h"
#include <filesystem>

namespace Durna
{
	void DirectoryScanner::GetFileInPath(const std::wstring& Path, std::vector<SystemFile>& OutFiles)
	{
		OutFiles.empty();

		if (Path == L"")
		{
			std::vector<VolumeGeometry> Volumes;
			DiskDriveHelpers::GetAllVolumes(Volumes);

			for (const VolumeGeometry& Volume : Volumes)
			{
				OutFiles.push_back(Volume.Path);
			}
		}

		else
		{
			for (const auto& file : std::filesystem::directory_iterator(Path))
			{
				OutFiles.push_back(file.path().wstring());
			}
		}
	}
}