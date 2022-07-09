#include "DurnaPCH.h"
#include "PointLightComponentPanel.h"

#if WITH_EDITOR

#include "Runtime/Components/Light/PointLightComponent.h"
#include "imgui.h"

namespace Durna
{
	PointLightComponentPanel::PointLightComponentPanel(PointLightComponent* InTarget)
		: Target(InTarget)
	{ }

	void Durna::PointLightComponentPanel::DrawPanel()
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

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("Attenuation");
					ImGui::TableNextColumn();
					ImGui::DragFloat("##LightAttenuation", &Target->Attenuation, 0.01f, 0.0f, 5.0f);

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("Visible");
					ImGui::TableNextColumn();
					ImGui::Checkbox("##Visibility", &Target->bVisible);

					ImGui::EndTable();
				}
			}
		}
	}
}

#endif