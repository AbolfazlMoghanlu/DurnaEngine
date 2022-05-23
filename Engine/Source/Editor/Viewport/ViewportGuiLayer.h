#pragma once

#if WITH_EDITOR
#include "Runtime/Renderer/ImGui/ImGuiLayer.h"

namespace Durna
{
	class ViewportGuiLayer : public ImGuiLayer
	{
	public:
		virtual void Draw() override;


	};
}

#endif