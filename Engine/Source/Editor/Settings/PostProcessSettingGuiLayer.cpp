#include "DurnaPCH.h"
#include "PostProcessSettingGuiLayer.h"

#if WITH_EDITOR
#include "imgui.h"
#include "Runtime/Renderer/Renderer.h"
#include "Editor/Settings/Settings.h"
#include "Runtime/Renderer/RenderTypes.h"

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
			ImGui::SliderFloat("Step Size", &Renderer::PPSetting.BlurStepSize, 0.0f, 0.01f);
			ImGui::SliderInt("Step Number", &Renderer::PPSetting.BlurStepNumber, 0, 5);
		}

		if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::ColorEdit3("Ambient Light Color", &Renderer::AmbientLightColor.R);
			ImGui::SliderFloat("Ambient Light Intensity", &Renderer::AmbientLightIntensity, 0, 5);

			ImGui::ColorEdit3("Diffuse Light Color", &Renderer::DiffuseLightColor.R);
			ImGui::SliderFloat("Diffuse Light Intensity", &Renderer::DiffuseLightIntensity, 0, 5);
			ImGui::SliderFloat3("Diffuse Light Rotation", &Renderer::DiffuseLightRation.Pitch, 0.0f, 360.0f);
		}

		ImGui::End();
	}
}
#endif