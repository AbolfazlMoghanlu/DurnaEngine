#include "DurnaPCH.h"
#include "ViewportGuiLayer.h"

#if WITH_EDITOR
#include "Runtime/Renderer/FrameBuffer/ResolveDefferedBuffer.h"
#include "Runtime/Renderer/Renderer.h"
#include "Editor/Settings/Settings.h"
#include "imgui.h"

LOG_DEFINE_CATEGORY(LogViewport, "Viewport");

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

		ImVec2 ViewportSize = ImGui::GetContentRegionAvail();
		if (!Math::IsNearlyEqual(ViewportSizeX, ViewportSize.x) || !Math::IsNearlyEqual(ViewportSizeY, ViewportSize.y))
		{
			OnViewportSizeChanged(ViewportSizeX, ViewportSize.x, ViewportSizeY, ViewportSize.y);

			ViewportSizeX = ViewportSize.x;
			ViewportSizeY = ViewportSize.y;
		}
		
		ImGui::Image((void*)Renderer::ResolvedBuffer->GetTextureID(), ViewportSize);

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

	void ViewportGuiLayer::OnViewportSizeChanged(float OldX, float NewX, float OldY, float NewY)
	{
		LOG(LogViewport, Info, "Viewport size changed to %f , %f", NewX, NewY);

		Renderer::OnResizeWindow(NewX, NewY);
	}
}

#endif
