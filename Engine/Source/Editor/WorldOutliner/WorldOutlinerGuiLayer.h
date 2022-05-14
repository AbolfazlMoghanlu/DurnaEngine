#pragma once

#include "Runtime/Renderer/ImGui/ImGuiLayer.h"

namespace Durna
{
#if WITH_EDITOR
	class WorldOutlinerGuiLayer : public ImGuiLayer
	{
	public:
		virtual void Draw() override;


	};
#endif
}