#include "DurnaPCH.h"
#include "WorldOutliner.h"

#include "Runtime/Engine/World.h"
#include "Runtime/Containers/List.h"
#include "Runtime/Engine/Actor.h"

#if WITH_EDITOR
#include "imgui.h"
#endif

namespace Durna
{
#if WITH_EDITOR

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
	{ }

	WorldOutliner* WorldOutliner::Get()
	{
		if (!SingletonInstance.get())
		{
			SingletonInstance = std::make_unique<WorldOutliner>();
		}

		return SingletonInstance.get();
	}

	void WorldOutlinerGuiLayer::Draw()
	{
		ImGui::Begin("World Outliner");

		for (LinkedListIterator It(World::Actors); It; ++It)
		{
			if (It)
			{
				ImGui::Text(It->GetActorLabel().c_str());
			}
		}

		ImGui::End();
	}

#endif
}