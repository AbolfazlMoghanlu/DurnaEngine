#include "DurnaPCH.h"
#include "DetailsPanel.h"

#if WITH_EDITOR

#include "Editor/DetailsPanel/DetailsPanelGuiLayer.h"

namespace Durna
{
	std::unique_ptr<DetailsPanel> DetailsPanel::SingletonInstance = nullptr;

	DetailsPanel::DetailsPanel()
	{ }

	DetailsPanel::~DetailsPanel()
	{ }

	void DetailsPanel::Init()
	{
		DetailsPanelGui = std::make_unique<DetailsPanelGuiLayer>();
		DetailsPanelGui->Attach();
	}

	void DetailsPanel::Tick(float DeltaTime)
	{

	}

	DetailsPanel* DetailsPanel::Get()
	{
		if (!SingletonInstance.get())
		{
			SingletonInstance = std::make_unique<DetailsPanel>();
		}

		return SingletonInstance.get();
	}
}

#endif