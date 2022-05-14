#pragma once

#if WITH_EDITOR

#include "Runtime/Renderer/ImGui/ImGuiLayer.h"

namespace Durna
{
	class DetailsPanelGuiLayer : public ImGuiLayer
	{
	public:
		virtual void Draw() override;

	protected:

	private:

	};
}

#endif