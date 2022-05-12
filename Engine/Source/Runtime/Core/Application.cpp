#include "DurnaPCH.h"
#include "Application.h"

#include "Runtime/Renderer/Renderer.h"
#include "Runtime/Window/Window.h"
#include "Runtime/Engine/World.h"

#include "Runtime/Engine/Camera/CameraManager.h"

LOG_DEFINE_CATEGORY(LogApp, "Application");

namespace Durna
{
	Application::Application()
	{
		
	}

	Application::~Application()
	{
		
	}

	void Application::Init()
	{
		LOG(LogApp, Info, "initializing.");
		Renderer::Init();
		
	}

	void Application::Tick(float DeltaTime)
	{
		World::Tick(DeltaTime);
		CameraManager::Get()->Tick(DeltaTime);
		Renderer::Tick(DeltaTime);
	}

	void Application::Shutdown()
	{
		Renderer::Shutdown();
		LOG(LogApp, Info, "shutingdown.");
	}

	bool Application::IsRunning() const
	{
		return Running && !Renderer::GetWindow()->IsClosing();
	}
}