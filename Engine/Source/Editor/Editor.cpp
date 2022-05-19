#include "DurnaPCH.h"
#include "Editor.h"

#if WITH_EDITOR
#include "Editor/WorldOutliner/WorldOutliner.h"
#include "Editor/DetailsPanel/DetailsPanel.h"
#include "Editor/Settings/Settings.h"
#include "Runtime/Engine/Actor.h"
#include "Runtime/Components/Component.h"

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
		Settings::Get()->Init();
	}

	void Editor::Tick(float DeltaTime)
	{
		WorldOutliner::Get()->Tick(DeltaTime);
		DetailsPanel::Get()->Tick(DeltaTime);
		Settings::Get()->Tick(DeltaTime);
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

	Actor* Editor::GetSelectedActor() const
	{
		return SelectedActor;
	}

	void Editor::SetSelectedComponent(SceneComponent* InComponent)
	{
		SelectedComponent = InComponent;
	}

	void Editor::ClearSelectedComponent()
	{
		SelectedComponent = nullptr;
	}

	SceneComponent* Editor::GetSelectedComponent() const
	{
		return SelectedComponent;
	}

}

#endif