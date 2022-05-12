#pragma once

// TODO: not working with pch
#include <memory>

namespace Durna
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Init();
		void Shutdown();

		virtual void Tick(float DeltaTime);

		static Application* Get();

		void RequestExit();
		bool IsRunning() const;

	private:
		bool bRunning = true;
		static std::unique_ptr<Application> SingletonInstance;

		friend class Engineloop;
	};
}

