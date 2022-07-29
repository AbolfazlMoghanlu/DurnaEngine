#pragma once

#include "Runtime/Misc/DiskDrive/DiskDriveTypes.h"

namespace Durna
{
	class DiskDriveHelpers
	{
	public:

		// @msdn
		// https://docs.microsoft.com/en-us/windows/win32/fileio/displaying-volume-paths
		static bool GetAllVolumes(std::vector<VolumeGeometry>& OutVolumes);
	};
}

