#include "DurnaPCH.h"
#include "ContentBrowserGuiLayer.h"

#if WITH_EDITOR
#include "imgui.h"

#include "Runtime/Misc/DiskDrive/DirectoryScanner.h"
#include "Runtime/Misc/DiskDrive/DiskDriveHelpers.h"

#include "Editor/Misc/FileMenu/FileMenu.h"


namespace Durna
{
	ContentBrowserGuiLayer::ContentBrowserGuiLayer()
	{
		ImportFileMenu = std::make_unique<FileMenu>("Import File", 800, 600, false);

		ImportFileMenu->BindOnCancel(std::bind(&ContentBrowserGuiLayer::OnImportCancel, this));
		ImportFileMenu->BindOnOK(std::bind(&ContentBrowserGuiLayer::OnImportFiles, this, std::placeholders::_1));
	}

	void ContentBrowserGuiLayer::Draw()
	{
		ImGui::Begin("Content Browser", (bool*)0, ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);

		ShowToolbar();

		ImGui::Separator();


		ImGui::End();

		ImportFileMenu->Draw();
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

	void ContentBrowserGuiLayer::OnClickedImprot()
	{
		ImportFileMenu->SetOpen(true);
	}

	void ContentBrowserGuiLayer::OnImportCancel()
	{
		
	}


	void ContentBrowserGuiLayer::OnImportFiles(const std::vector<SystemFile>& Files)
	{
	
	}

}

#endif