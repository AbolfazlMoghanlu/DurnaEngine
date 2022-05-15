#include "DurnaPCH.h"
#include "WorldOutliner.h"

#if WITH_EDITOR
#include "Editor/WorldOutliner/WorldOutlinerGuiLayer.h"
#include "Runtime/Engine/Actor.h"

namespace Durna
{
	std::unique_ptr<WorldOutliner> WorldOutliner::SingletonInstance = nullptr;

	WorldOutliner::WorldOutliner()
	{ }

	WorldOutliner::~WorldOutliner()
	{ }

	void WorldOutliner::Init()
	{
		OutlinerGui = std::make_unique<WorldOutlinerGuiLayer>();	
		OutlinerGui->Attach();
	}

	void WorldOutliner::Tick(float DeltaTime)
	{
		
	}

	WorldOutliner* WorldOutliner::Get()
	{
		if (!SingletonInstance.get())
		{
			SingletonInstance = std::make_unique<WorldOutliner>();
		}

		return SingletonInstance.get();
	}
}

#endif