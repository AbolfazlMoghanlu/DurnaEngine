#include "DurnaPCH.h"
#include "FileMenu.h"

#if WITH_EDITOR
#include "imgui.h"
#include "Runtime/Misc/DiskDrive/DirectoryScanner.h"

namespace Durna
{
	FileMenu::FileMenu(const std::string& InTitle, int32 InSizeX /*= 800*/, int32 InSizeY /*= 600*/, bool Open /*= true*/)
		: Title(InTitle)
		, SizeX(InSizeX)
		, SizeY(InSizeY)
		, bOpen(Open)
	{ }

	void FileMenu::Draw()
	{
		if (!bOpen)
		{
			return;
		}

		ImGui::SetNextWindowSize(ImVec2(800, 600));

		int32 MenuFlags = ImGuiWindowFlags_::ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse;

		ImGui::Begin("Import File", &bOpen, MenuFlags);


		bool bRoot = CurrentDirectory == L"";


		if (!bRoot)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.72f, 0.72f, 0.17f, 1));

			if (ImGui::Button(".."))
			{
				SelectedFiles.clear();

				int32 SecondLastSlash = CurrentDirectory.rfind(L"\\", CurrentDirectory.size() - 2);

				if (SecondLastSlash >= 0)
				{
					CurrentDirectory = CurrentDirectory.substr(0, SecondLastSlash + 1);
				}

				else
				{
					CurrentDirectory = L"";
				}
			}

			ImGui::PopStyleColor();
		}

		const ImVec2 AvaliableRegion = ImGui::GetContentRegionAvail();
		ImGui::BeginChild("FileList", ImVec2(AvaliableRegion.x, AvaliableRegion.y * 0.9f),
			false);

		std::vector<SystemFile> FilesInCurrentPath;
		DirectoryScanner::GetFileInPath(CurrentDirectory, FilesInCurrentPath);

		for (const SystemFile& SF : FilesInCurrentPath)
		{
			std::string FileName = std::string(SF.Name.begin(), SF.Name.end());

			bool bFileSelected = false;

			ImVec4 ButtonColor;
			if (SF.bDirectory)
			{
				ButtonColor = ImVec4(0.12f, 0.72f, 0.17f, 1);
			}
			else
			{
				bFileSelected = SelectedFilesContains(SF);
			
				ButtonColor = bFileSelected ? ImVec4(1.0f, 0.0f, 1.0f, 1) : ImVec4(0.12f, 0.17f, 0.72f, 1);
			}

			ImGui::PushStyleColor(ImGuiCol_Button, ButtonColor);


			if (ImGui::Button(FileName.c_str()))
			{
				if (SF.bDirectory)
				{
					CurrentDirectory = CurrentDirectory + SF.Name + L"\\";
				}

				else
				{
					if (bFileSelected)
					{
						for (auto& It = SelectedFiles.begin(); It != SelectedFiles.end(); It++)
						{
							if (It->Name == SF.Name)
							{
								SelectedFiles.erase(It);
								break;
							}
						}
					}
					else
					{
						SelectedFiles.push_back(SF);
					}
				}
			}

			ImGui::PopStyleColor();
		}

		ImGui::EndChild();

		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		
		
		if (ImGui::Button("OK"))
		{
			OnClickedOK();
		}

		ImGui::SameLine();

		if (ImGui::Button("Cancel"))
		{
			OnClickCancel();
		}

		ImGui::End();
	}

	void FileMenu::SetOpen(bool Open)
	{
		bOpen = Open;
	}

	void FileMenu::BindOnCancel(const std::function<void()>& InFun)
	{
		OnClickedCancelFun = InFun;
	}

	void FileMenu::BindOnOK(const std::function<void(const std::vector<SystemFile>& Files)>& InFun)
	{
		OnClickedOKFun = InFun;
	}

	void FileMenu::OnClickedOK()
	{
		if (OnClickedOKFun)
		{
			OnClickedOKFun(SelectedFiles);
		}

		bOpen = false;
		SelectedFiles.clear();
	}

	void FileMenu::OnClickCancel()
	{
		if (OnClickedCancelFun)
		{
			OnClickedCancelFun();
		}

		bOpen = false;
		SelectedFiles.clear();
	}

	bool FileMenu::SelectedFilesContains(const SystemFile& InSystemFile) const
	{
		for (const SystemFile& SelectedFile : SelectedFiles)
		{
			if (SelectedFile.Name == InSystemFile.Name)
			{
				return true;
			}
		}

		return false;
	}

}

#endif