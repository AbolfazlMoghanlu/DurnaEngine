#include "DurnaPCH.h"
#include "Runtime/Launch/LaunchEngineLoop.h"

#include "Runtime/Core/Application.h"

LOG_DEFINE_CATEGORY(LogEngine, "Engine");

extern Durna::Application* CreateApplication();

namespace Durna
{
	Engineloop engineLoop;

	Engineloop::Engineloop() :
		MaxTimeDilation(1 / 9999.0f)
		, LastTickTime(-1.0f)
	{

	}

	Engineloop::~Engineloop()
	{

	}

	bool Engineloop::Init()
	{
		LOG(LogEngine, Info, "Initalizing.");

		App = CreateApplication();
		if (App)
		{
			App->Init();
			return true;
		}

		return App != nullptr;
	}

	void Engineloop::Shutdown()
	{
		LOG(LogEngine, Info, "End play. Shuting down.");

		App->Shutdown();
		delete App;

		LOG(LogEngine, Info, "Shut down successfully.");
	}

	void Engineloop::MainLoop()
	{
		std::chrono::duration<double, std::milli> TimeDuration = std::chrono::high_resolution_clock::now().time_since_epoch();
		engineLoop.LastTickTime = TimeDuration.count() / 1000;

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
		//std::cout << 1 / DeltaTime << std::endl;

		App->Tick(DeltaTime);
	}
}

int main()
{
	if (!Durna::engineLoop.Init())
	{
		LOG(LogEngine, Error, "Failed to initialize engine.");
		return -1;
	}
	
	// engine main loop
	Durna::engineLoop.MainLoop();

	Durna::engineLoop.Shutdown();
}