#include "DurnaPCH.h"
#include "DiskDriveHelpers.h"


namespace Durna
{
	std::wstring GetVolumePaths(PWCHAR VolumeName)
	{
		DWORD  CharCount = MAX_PATH + 1;
		PWCHAR Names = NULL;
		PWCHAR NameIdx = NULL;
		BOOL   Success = FALSE;

		Names = (PWCHAR) new BYTE[CharCount * sizeof(WCHAR)];
		if(!Names)	{return L"";}

		Success = GetVolumePathNamesForVolumeNameW(VolumeName, Names, CharCount, &CharCount);
		if (!Success)	{ return L""; }

		std::wstring name = Names;

		delete[] Names;
		return name;
	}

	void SortVolumesByPath(std::vector<VolumeGeometry>& Volumes)
	{
		if (Volumes.size() < 1)	{ return; }

		for (int32 i = 0; i < Volumes.size(); i++)
		{
			int32 Min = i;

			for (int32 j = i + 1; j < Volumes.size(); j++)
			{
				Min = Volumes[Min].Path.compare(Volumes[j].Path) < 0 ? Min : j;
			}

			VolumeGeometry Temp = Volumes[i];
			Volumes[i] = Volumes[Min];
			Volumes[Min] = Temp;
		}
	}


	bool DiskDriveHelpers::GetAllVolumes(std::vector<VolumeGeometry>& OutVolumes)
	{
		OutVolumes.clear();

		HANDLE FindHandle;
		WCHAR VolumeName[MAX_PATH] = L"";
		DWORD Error;

		FindHandle = FindFirstVolumeW(VolumeName, ARRAYSIZE(VolumeName));

		if (FindHandle == INVALID_HANDLE_VALUE)
		{
			Error = GetLastError();
			wprintf(L"FindFirstVolumeW failed with error code %d\n", Error);

			return false;
		}

		while (true)
		{
			//  Skip the \\?\ prefix and remove the trailing backslash.
			size_t Index = wcslen(VolumeName) - 1;

			if (VolumeName[0] != L'\\' ||
				VolumeName[1] != L'\\' ||
				VolumeName[2] != L'?' ||
				VolumeName[3] != L'\\' ||
				VolumeName[Index] != L'\\')
			{
				Error = ERROR_BAD_PATHNAME;
				wprintf(L"FindFirstVolumeW/FindNextVolumeW returned a bad path: %s\n", VolumeName);
				break;
			}

			//  QueryDosDeviceW does not allow a trailing backslash,
			//  so temporarily remove it.
			VolumeName[Index] = L'\0';

			WCHAR DeviceName[MAX_PATH];
			DWORD CharCount = QueryDosDeviceW(&VolumeName[4], DeviceName, ARRAYSIZE(DeviceName));

			VolumeName[Index] = L'\\';

			if (CharCount == 0)
			{
				Error = GetLastError();
				wprintf(L"QueryDosDeviceW failed with error code %d\n", Error);
				break;
			}
			
			std::wstring Path = GetVolumePaths(VolumeName);
			if (Path != L"")
			{
				int32 PathFirstSlash = Path.find_first_of(L"\\");
				std::wstring CroppedPath = PathFirstSlash >= 0 ? Path.substr(0, PathFirstSlash) : Path;
			
				OutVolumes.push_back(VolumeGeometry(std::wstring(VolumeName), CroppedPath));
			}

			bool Success = FindNextVolumeW(FindHandle, VolumeName, ARRAYSIZE(VolumeName));

			if (!Success)
			{
				Error = GetLastError();

				if (Error != ERROR_NO_MORE_FILES)
				{
					wprintf(L"FindNextVolumeW failed with error code %d\n", Error);
					break;
				}

				//  Finished iterating
				//  through all the volumes.
				Error = ERROR_SUCCESS;
				break;
			}
		}


		FindVolumeClose(FindHandle);
		FindHandle = INVALID_HANDLE_VALUE;

		SortVolumesByPath(OutVolumes);

		return true;
	}

}