#include "DurnaPCH.h"
#include "Application.h"

#include "Runtime/Renderer/Renderer.h"
#include "Runtime/Window/Window.h"

namespace Durna
{
	void Application::Init()
	{
		Renderer::Init();
	}

	void Application::Shutdown()
	{
		Renderer::Shutdown();
	}

	bool Application::IsRunning() const
	{
		return Running;
	}

}