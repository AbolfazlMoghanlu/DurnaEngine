#include "DurnaPCH.h"
#include "PostProcessSettingGuiLayer.h"

#if WITH_EDITOR
#include "imgui.h"
#include "Runtime/Renderer/Renderer.h"

namespace Durna
{
	void PostProcessSettingGuiLayer::Draw()
	{
		ImGui::Begin("Post Process Setting");

		// Fog
		if (ImGui::CollapsingHeader("Fog", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::ColorEdit3("Color", &Renderer::PPSetting.FogColor.R);
			ImGui::SliderFloat("Amount", &Renderer::PPSetting.FogAmount, 0.0f, 5.0f);
			ImGui::SliderFloat("Offset", &Renderer::PPSetting.FogOffset, 0.0f, 5.0f);
			ImGui::SliderFloat("Length", &Renderer::PPSetting.FogLength, 0.0f, 5.0f);
		}

		// Blur
		if (ImGui::CollapsingHeader("Blur", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::SliderFloat("Step Size", &Renderer::PPSetting.BlurStepSize, 0.0f, 0.02f);
			ImGui::SliderInt("Step Number", &Renderer::PPSetting.BlurStepNumber, 0, 5);
		}

		ImGui::End();
	}
}
#endif