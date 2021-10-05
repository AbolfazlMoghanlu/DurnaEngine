#include "DurnaPCH.h"
#include "Runtime/Launch/LaunchEngineLoop.h"

#include "Runtime/Core/Application.h"

namespace Durna
{
	Engineloop engineLoop;

	bool Engineloop::Init()
	{
		App = new Application();
		App->Init();

		return true;
	}

	void Engineloop::Shutdown()
	{
		delete App;
	}

	void Engineloop::MainLoop()
	{
		while (App->IsRunning())
		{
			// Calculating time dilation
			std::chrono::duration<double, std::milli> TimeDuration = std::chrono::high_resolution_clock::now().time_since_epoch();
			double CurrentTime = TimeDuration.count() / 1000;

			float DeltaTime = static_cast<float>(CurrentTime - engineLoop.LastTickTime);

			// checking tickrate limitation
			if (DeltaTime < MaxTimeDilation)
			{
				continue;
			}
			engineLoop.LastTickTime = CurrentTime;

			engineLoop.Tick(DeltaTime);
		}
	}

	void Engineloop::Tick(float DeltaTime)
	{
		// prints framerate
		std::cout << 1 / DeltaTime << std::endl;

		App->Tick(DeltaTime);
	}
}

int main()
{
	std::cout << "Engine started.";

	if (!Durna::engineLoop.Init())
	{
		// todo: error log
		return -1;
	}

	// engine main loop
	Durna::engineLoop.MainLoop();

	Durna::engineLoop.Shutdown();
}