#include "DurnaPCH.h"
#include "ViewportGuiLayer.h"

#if WITH_EDITOR
#include "Editor/Viewport/Viewport.h"
#include "Runtime/Renderer/FrameBuffer/ResolveDefferedBuffer.h"
#include "Runtime/Renderer/Renderer.h"
#include "Runtime/Renderer/RenderCommands.h"
#include "Editor/Settings/Settings.h"
#include "imgui.h"
#include "Editor/Editor.h"
#include "Runtime/Renderer/FrameBuffer/FrameBuffer.h"
#include "Runtime/Renderer/FrameBuffer/GBuffer.h"

LOG_DEFINE_CATEGORY(LogViewport, "Viewport");

namespace Durna
{
	void ViewportGuiLayer::Draw()
	{
		ImGui::Begin("Viewport", (bool*) 0, ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);

		if(ImGui::BeginMenuBar())
		{
			ShowDisplayBufferMenuItem();
			ShowResolutionOption();

			ImGui::PushItemWidth(200);
			ImGui::SliderFloat("Camera Speed", &Editor::Get()->CameraMoveSpeed, 0.5f, 20.0f);
			ImGui::PopItemWidth();

			ImGui::EndMenuBar();
		}

		const ImVec2 AvaliableSize = ImGui::GetContentRegionAvail();
		const IntPoint ImageSize = IntPoint((int32)AvaliableSize.x, (int32)AvaliableSize.y);

		if (ViewportImageSize != ImageSize)
		{
			OnViewportSizeChanged(ViewportImageSize, ImageSize);
			ViewportImageSize = ImageSize;
		}

		ImGui::Image((void*)(size_t)(Renderer::Gbuffer->Attachments[7]->TextureID), AvaliableSize, 
			ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();
	}

	void ViewportGuiLayer::ShowDisplayBufferMenuItem()
	{
		int32* DisplayMode = (int32*)(&Settings::Get()->GetDisplayBuffer());

		if (ImGui::BeginMenu(DisplayBufferToString(*DisplayMode).c_str()))
		{
			for (int i = 0; i < static_cast<int32>(DisplayBuffer::Max); i++)
			{
				if (ImGui::MenuItem(DisplayBufferToString(i).c_str(), NULL, i == *DisplayMode))
				{
					*DisplayMode = i;
				}
			}

			ImGui::EndMenu();
		}
	}

	void ViewportGuiLayer::ShowResolutionOption()
	{
		ImGui::Checkbox("Custom Resolution", &Viewport::Get()->bCustomResolution);

		ImGui::BeginDisabled(!Viewport::Get()->bCustomResolution);

		ImGui::PushItemWidth(80.0f);
		ImGui::InputInt2("", &Viewport::Get()->Resolution.X);
		ImGui::PopItemWidth();

		ImGui::EndDisabled();
	}

	void ViewportGuiLayer::OnViewportSizeChanged(const IntPoint& OldSize, const IntPoint& NewSize)
	{
		LOG(LogViewport, Info, "Viewport size changed to %i , %i", NewSize.X, NewSize.Y);

		Viewport::Get()->OnViewportSizeChanged(OldSize, NewSize);
	}
}

#endif
