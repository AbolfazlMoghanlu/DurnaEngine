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

		int32 a = 0;

		ImGui::Text("Display Buffer");

		int32* DisplayMode = (int32*)(&Settings::Get()->DisplayBufferMode);

		ImGui::RadioButton("FinalColor",	 DisplayMode, 0);
		ImGui::RadioButton("BaseColor",		 DisplayMode, 1);
		ImGui::RadioButton("WorldNormal",	 DisplayMode, 2);
		ImGui::RadioButton("SceneDepth",	 DisplayMode, 3);
		ImGui::RadioButton("Stencil",		 DisplayMode, 4);

		ImGui::Separator();

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

		ImGui::End();
	}
}
#endif