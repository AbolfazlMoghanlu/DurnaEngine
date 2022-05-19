#pragma once

#if WITH_EDITOR

#include "Runtime/Renderer/ImGui/ImGuiLayer.h"

namespace Durna
{
	class PostProcessSettingGuiLayer : public ImGuiLayer
	{
	public:
		virtual void Draw() override;
	};
}

#endif