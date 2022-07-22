#include "DurnaPCH.h"
#include "ContentBrowser.h"

#if WITH_EDITOR
#include "Editor/ContentBrowser/ContentBrowserGuiLayer.h"

namespace Durna
{
	std::unique_ptr<ContentBrowser> ContentBrowser::SingletonInstance;

	ContentBrowser::ContentBrowser()
	{ }

	ContentBrowser::~ContentBrowser()
	{ }

	void ContentBrowser::Init()
	{
		OutputLogLayer = std::make_unique<ContentBrowserGuiLayer>();
		OutputLogLayer->Attach();
	}

	void ContentBrowser::Tick(float DeltaTime)
	{

	}

	ContentBrowser* ContentBrowser::Get()
	{
		if (!SingletonInstance)
		{
			SingletonInstance = std::make_unique<ContentBrowser>();
		}

		return SingletonInstance.get();
	}
}

#endif