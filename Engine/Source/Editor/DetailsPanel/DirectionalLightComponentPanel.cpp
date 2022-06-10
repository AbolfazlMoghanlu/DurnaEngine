#include "DurnaPCH.h"
#include "DirectionalLightComponentPanel.h"

#if WITH_EDITOR

#include "Runtime/Components/DirectionalLightComponent.h"
#include "imgui.h"

namespace Durna
{
	DirectionalLightComponentPanel::DirectionalLightComponentPanel(DirectionalLightComponent* InTarget)
		: Target(InTarget)
	{ }

	 
	void DirectionalLightComponentPanel::DrawPanel()
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
					ImGui::Text("Cast Shadow");
					ImGui::TableNextColumn();
					ImGui::Checkbox("##CastShadow", &Target->bCastShadow);

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("Shadow Resolution");
					ImGui::TableNextColumn();
	
					if (!bChachedCastShadow)
						ImGui::BeginDisabled();
					
					ImGui::DragInt("##ShadowResolution", &Target->ShadowResolution, 1, 32, 2048);

					if (!bChachedCastShadow)
						ImGui::EndDisabled();

					ImGui::EndTable();
				}
			}

			if (bChachedCastShadow != Target->bCastShadow)
			{
				bChachedCastShadow = Target->bCastShadow;
				Target->SetCastShadow(bChachedCastShadow);
			}

			if (CachedShadowResolution != Target->GetShadowResolution())
			{
				CachedShadowResolution = Target->GetShadowResolution();
				Target->SetShadowResolution(CachedShadowResolution);
			}
		}
	}
}

#endif