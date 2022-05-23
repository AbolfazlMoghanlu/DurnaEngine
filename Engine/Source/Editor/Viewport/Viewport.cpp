#include "DurnaPCH.h"
#include "Viewport.h"

#if WITH_EDITOR
#include "Editor/Viewport/ViewportGuiLayer.h"

namespace Durna
{
	std::unique_ptr<Durna::Viewport> Viewport::SingletonInstance;

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

	}

	Viewport* Viewport::Get()
	{
		if (!SingletonInstance.get())
		{
			SingletonInstance = std::make_unique<Viewport>();
		}

		return SingletonInstance.get();
	}
}

#endif