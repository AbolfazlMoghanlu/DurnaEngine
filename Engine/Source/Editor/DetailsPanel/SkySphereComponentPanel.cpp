#include "DurnaPCH.h"
#include "SkySphereComponentPanel.h"

#if WITH_EDITOR

#include "Runtime/Components/SkySphereComponent.h"
#include "imgui.h"

namespace Durna
{

	SkySphereComponentPanel::SkySphereComponentPanel(SkySphereComponent* InTarget) :
		Target(InTarget)
	{ }

	void SkySphereComponentPanel::DrawPanel()
	{
		if (Target)
		{
			if (ImGui::CollapsingHeader("Color", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
			{
				if (ImGui::BeginTable("##ColorCategory", 2))
				{
					ImGui::TableNextColumn();
					ImGui::Text("Overall Color");
					ImGui::TableNextColumn();
					ImGui::ColorEdit4("##LightColor", &Target->OverallColor.R);

					ImGui::EndTable();
				}
			}
		}

	}
}

#endif