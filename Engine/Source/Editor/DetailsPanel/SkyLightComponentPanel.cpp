#include "DurnaPCH.h"
#include "SkyLightComponentPanel.h"

#if WITH_EDITOR

#include "Runtime/Components/SkyLightComponent.h"
#include "imgui.h"

namespace Durna
{
	SkyLightComponentPanel::SkyLightComponentPanel(SkyLightComponent* InTarget)
		: Target(InTarget)
	{ }

	void SkyLightComponentPanel::DrawPanel()
	{
		if (Target)
		{
			if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
			{
				if (ImGui::BeginTable("##LightCategory", 2))
				{
					ImGui::TableNextColumn();
					ImGui::Text("Intensity");
					ImGui::TableNextColumn();
					ImGui::DragFloat("##Intensity", &Target->Intensity, 0.1f, 0.0f, 100.0f);

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("Light Color");
					ImGui::TableNextColumn();
					ImGui::ColorEdit4("##LightColor", &Target->LightColor.R);

					ImGui::EndTable();
				}
			}
		}
	}
}

#endif