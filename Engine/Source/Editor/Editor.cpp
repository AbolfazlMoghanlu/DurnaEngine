#include "DurnaPCH.h"
#include "Editor.h"

#if WITH_EDITOR
#include "Editor/WorldOutliner.h"

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
	}

	void Editor::Tick(float DeltaTime)
	{
		WorldOutliner::Get()->Tick(DeltaTime);
	}

	Editor* Editor::Get()
	{
		if (!SingletonInstance.get())
		{
			SingletonInstance = std::make_unique<Editor>();
		}

		return SingletonInstance.get();
	}

}

#endif