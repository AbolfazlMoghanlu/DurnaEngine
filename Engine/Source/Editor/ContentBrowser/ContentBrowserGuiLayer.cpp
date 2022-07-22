#include "DurnaPCH.h"
#include "ContentBrowserGuiLayer.h"

#if WITH_EDITOR
#include "imgui.h"


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


		ImGui::End();
	}

	void ContentBrowserGuiLayer::OnClickedImprot()
	{
		bImportFileOpen = true;
	}

}

#endif