#pragma once


#if WITH_EDITOR
#include "Runtime/Misc/DiskDrive/DiskDriveTypes.h"

namespace Durna
{
	class FileMenu
	{
	public:
		FileMenu(const std::string& InTitle, int32 InSizeX = 800, int32 InSizeY = 600, bool Open = true);

		virtual void Draw();

		void SetOpen(bool Open);

		void BindOnCancel(const std::function<void()>& InFun);
		void BindOnOK(const std::function<void(const std::vector<SystemFile>& Files)>& InFun);

	protected:
		std::string Title;
		int32 SizeX;
		int32 SizeY;

		std::wstring CurrentDirectory = L"";
		bool bOpen;

		virtual void OnClickedOK();
		virtual void OnClickCancel();

		std::function<void()> OnClickedCancelFun;
		std::function<void(const std::vector<SystemFile>& Files)> OnClickedOKFun;
	
	private:
	};
}
#endif