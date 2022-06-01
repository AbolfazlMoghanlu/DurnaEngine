#include "DurnaPCH.h"
#include "Viewport.h"

#if WITH_EDITOR
#include "Editor/Viewport/ViewportGuiLayer.h"
#include "Runtime/Renderer/RenderCommands.h"

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
			RenderCommands::SetWindowResolution(Resolution);
			PreviousFrameResolution = Resolution;
		}

		else if (!bCustomResolution && Resolution != ViewportLayer->ViewportImageSize)
		{
			Resolution = ViewportLayer->ViewportImageSize;
			RenderCommands::SetWindowResolution(Resolution);
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
			RenderCommands::SetWindowResolution(Resolution);
		}
	}
}

#endif