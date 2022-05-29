#pragma once

#if WITH_EDITOR
#include "Runtime/Renderer/ImGui/ImGuiLayer.h"

namespace Durna
{
	class ViewportGuiLayer : public ImGuiLayer
	{
	public:
		virtual void Draw() override;


	private:
		void ShowDisplayBufferMenuItem();

		void OnViewportSizeChanged(float OldX, float NewX, float OldY, float NewY);


		float ViewportSizeX = 0;
		float ViewportSizeY = 0;
	};
}

#endif