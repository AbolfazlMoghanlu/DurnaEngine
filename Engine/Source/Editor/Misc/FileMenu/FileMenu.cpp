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


			if (SF.bDirectory)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.12f, 0.72f, 0.17f, 1));
			}
			else
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.12f, 0.17f, 0.72f, 1));
			}

			if (ImGui::Button(FileName.c_str()))
			{
				if (SF.bDirectory)
				{
					CurrentDirectory = CurrentDirectory + SF.Name + L"\\";
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
		bOpen = false;

		if (OnClickedOKFun)
		{
			std::vector<SystemFile> Files;
			Files.push_back(SystemFile(L"D:"));
			OnClickedOKFun(Files);
		}
	}

	void FileMenu::OnClickCancel()
	{
		bOpen = false;

		if (OnClickedCancelFun)
		{
			OnClickedCancelFun();
		}
	}
}

#endif