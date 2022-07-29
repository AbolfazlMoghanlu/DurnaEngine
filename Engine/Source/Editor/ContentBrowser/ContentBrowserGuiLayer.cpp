#include "DurnaPCH.h"
#include "ContentBrowserGuiLayer.h"

#if WITH_EDITOR
#include "imgui.h"

#include "Runtime/Misc/DiskDrive/DirectoryScanner.h"
#include "Runtime/Misc/DiskDrive/DiskDriveHelpers.h"
#include "Runtime/Misc/DiskDrive/DiskDriveTypes.h"

namespace Durna
{
	void ContentBrowserGuiLayer::Draw()
	{
		ImGui::Begin("Content Browser", (bool*)0, ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);

		ShowToolbar();

		ImGui::Separator();
		
		if (bImportFileOpen)
		{
			ShowImportFileMenu();
		}
		
		
		ImGui::End();
	}

	void ContentBrowserGuiLayer::ShowToolbar()
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.47f, 0.72f, 0.47f, 1));
		if (ImGui::Button("Import"))
		{
			OnClickedImprot();
		}
		ImGui::PopStyleColor();


	}

	void ContentBrowserGuiLayer::ShowImportFileMenu()
	{
		ImGui::SetNextWindowSize(ImVec2(800, 600));

		int32 MenuFlags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar |ImGuiWindowFlags_::ImGuiWindowFlags_NoDocking |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse;

		ImGui::Begin("Import File", &bImportFileOpen, MenuFlags);


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

		ImGui::End();
	}

	void ContentBrowserGuiLayer::OnClickedImprot()
	{
		bImportFileOpen = true;
	}

}

#endif