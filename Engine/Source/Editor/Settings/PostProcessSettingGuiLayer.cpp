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

		ImGui::ColorEdit3("FogColor", &Renderer::PPSetting.FogColor.R);
		ImGui::SliderFloat("FogAmount", &Renderer::PPSetting.FogAmount, 0.0f, 5.0f);
		ImGui::SliderFloat("FogOffset", &Renderer::PPSetting.FogOffset, 0.0f, 5.0f);
		ImGui::SliderFloat("FogLength", &Renderer::PPSetting.FogLength, 0.0f, 5.0f);

		ImGui::End();
	}
}
#endif