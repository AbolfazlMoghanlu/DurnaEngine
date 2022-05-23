#include "DurnaPCH.h"
#include "ViewportGuiLayer.h"

#if WITH_EDITOR
#include "Runtime/Renderer/FrameBuffer/ResolveDefferedBuffer.h"
#include "Runtime/Renderer/Renderer.h"
#include "imgui.h"

namespace Durna
{
	void ViewportGuiLayer::Draw()
	{
		ImGui::Begin("Viewport");

		

		ImGui::Image((void*)Renderer::ResolvedBuffer->GetTextureID(), ImGui::GetWindowSize());
		


		ImGui::End();
	}
}

#endif
