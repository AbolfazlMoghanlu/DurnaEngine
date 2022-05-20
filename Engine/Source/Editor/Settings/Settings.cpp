#include "DurnaPCH.h"
#include "Settings.h"

#if WITH_EDITOR

#include "Editor/Settings/PostProcessSettingGuiLayer.h"

namespace Durna
{
	std::unique_ptr<Durna::Settings> Settings::SingletonInstance = nullptr;

	Settings::Settings()
	{ }

	Settings::~Settings()
	{ }

	void Settings::Init()
	{
		OutlinerGui = std::make_unique<PostProcessSettingGuiLayer>();
		OutlinerGui->Attach();
	}

	void Settings::Tick(float DeltaTime)
	{

	}

	Settings* Settings::Get()
	{
		if (!SingletonInstance.get())
		{
			SingletonInstance = std::make_unique<Settings>();
		}

		return SingletonInstance.get();
	}

	DisplayBuffer Settings::GetDisplayBuffer() const
	{
		return DisplayBufferMode;
	}
}

#endif