#include "DurnaPCH.h"
#include "ViewportGuiLayer.h"

#if WITH_EDITOR
#include "Runtime/Renderer/FrameBuffer/ResolveDefferedBuffer.h"
#include "Runtime/Renderer/Renderer.h"
#include "Editor/Settings/Settings.h"
#include "imgui.h"

namespace Durna
{
	void ViewportGuiLayer::Draw()
	{
		ImGui::Begin("Viewport", (bool*) 0, ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);

		if(ImGui::BeginMenuBar())
		{
			ShowDisplayBufferMenuItem();

			ImGui::EndMenuBar();
		}

		const ImVec2 WindowSize = ImGui::GetWindowSize();
		ImVec2 WindowSizeYPadded(WindowSize.x, WindowSize.y - 35);
		ImGui::Image((void*)Renderer::ResolvedBuffer->GetTextureID(), WindowSizeYPadded);

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

}

#endif
