#include "DurnaPCH.h"
#include "ImGuiLayer.h"

#include "Runtime/Renderer/ImGui/ImGuiRenderer.h"

namespace Durna
{
	ImGuiLayer::ImGuiLayer()
	{ }

	ImGuiLayer::~ImGuiLayer()
	{ }

	void ImGuiLayer::Attach()
	{
		ImGuiRenderer::Get()->AttachLayer(this);
	}

	void ImGuiLayer::DeAttach()
	{ }
}