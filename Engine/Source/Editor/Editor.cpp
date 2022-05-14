#include "DurnaPCH.h"
#include "Editor.h"

#if WITH_EDITOR
#include "Editor/WorldOutliner/WorldOutliner.h"
#include "Editor/DetailsPanel/DetailsPanel.h"
#include "Runtime/Engine/Actor.h"

namespace Durna
{
	std::unique_ptr<Editor> Editor::SingletonInstance;
	
	Editor::Editor()
	{ }

	Editor::~Editor()
	{ }

	void Editor::Init()
	{
		WorldOutliner::Get()->Init();
		DetailsPanel::Get()->Init();
	}

	void Editor::Tick(float DeltaTime)
	{
		WorldOutliner::Get()->Tick(DeltaTime);
		DetailsPanel::Get()->Tick(DeltaTime);
	}

	Editor* Editor::Get()
	{
		if (!SingletonInstance.get())
		{
			SingletonInstance = std::make_unique<Editor>();
		}

		return SingletonInstance.get();
	}

	void Editor::SetSelectedActor(Actor* InActor)
	{
		SelectedActor = InActor;
	}

	void Editor::ClearSelectedActor()
	{
		SelectedActor = nullptr;
	}

	Actor* Editor::GetSelectedActor()
	{
		return SelectedActor;
	}
}

#endif