#include "DurnaPCH.h"
#include "GameSettings.h"
#include "Runtime/Renderer/RenderCommands.h"
#include "Runtime/Renderer/Renderer.h"
#include "Runtime/Window/Window.h"

namespace Durna
{
	std::unique_ptr<GameSettings> GameSettings::SingletonInstance = nullptr;

	GameSettings::GameSettings()
	{ }

	GameSettings::~GameSettings()
	{ }

	GameSettings* GameSettings::Get()
	{
		if (!SingletonInstance.get())
		{
			SingletonInstance = std::make_unique<GameSettings>();
		}

		return SingletonInstance.get();
	}

	EWindowMode GameSettings::GetWindowMode() const
	{
		return WindowMode;
	}

	void GameSettings::SetWindowMode(EWindowMode InWindowMode)
	{
		WindowMode = InWindowMode;
	}

	IntPoint GameSettings::GetResolution() const
	{
		return Resolution;
	}

	void GameSettings::SetResolution(const IntPoint& InSize)
	{
		Resolution = InSize;
	}

	void GameSettings::ApplySettings()
	{
		ApplyResolutionSetting();	
	}

	void GameSettings::ApplyResolutionSetting()
	{
		RenderCommands::SetWindowResolution(Resolution);
		RenderCommands::SetWindowMode(WindowMode);
		Renderer::GetWindow()->UpdateWindowSettings();
	}
}