#include "DurnaPCH.h"
#include "Runtime/Launch/LaunchEngineLoop.h"

#include <ctime>

namespace Durna
{
	Engineloop engineLoop;

	void Engineloop::StartLoop()
	{
		while (true) // todo: based on application running flag
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
	Durna::engineLoop.StartLoop();

	Durna::engineLoop.Shutdown();
}