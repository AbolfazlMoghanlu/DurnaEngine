#include "DurnaPCH.h"
#include "Viewport.h"

#if WITH_EDITOR
#include "Editor/Viewport/ViewportGuiLayer.h"
#include "Runtime/Renderer/RenderCommands.h"
#include "Runtime/Renderer/Renderer.h"
#include "Runtime/Window/Window.h"

namespace Durna
{
	std::unique_ptr<Viewport> Viewport::SingletonInstance;

	Viewport::Viewport()
	{ }

	Viewport::~Viewport()
	{ }

	void Viewport::Init()
	{
		ViewportLayer = std::make_unique<ViewportGuiLayer>();
		ViewportLayer->Attach();
	}

	void Viewport::Tick(float DeltaTime)
	{
		if (bCustomResolution && PreviousFrameResolution != Resolution)
		{
			PreviousFrameResolution = Resolution;
			UpdateViewport();
		}

		else if (!bCustomResolution && Resolution != ViewportLayer->ViewportImageSize)
		{
			Resolution = ViewportLayer->ViewportImageSize;
			UpdateViewport();
		}
	}

	Viewport* Viewport::Get()
	{
		if (!SingletonInstance.get())
		{
			SingletonInstance = std::make_unique<Viewport>();
		}

		return SingletonInstance.get();
	}

	void Viewport::OnViewportSizeChanged(const IntPoint& OldSize, const IntPoint& NewSize)
	{
		if (!bCustomResolution)
		{
			Resolution = NewSize;
		}
		UpdateViewport();
	}

	void Viewport::UpdateViewport()
	{
		Renderer::GetWindow()->SetWindowResolution(Resolution);
		Renderer::OnResolutionChanged(Resolution);
	}
}

#endif