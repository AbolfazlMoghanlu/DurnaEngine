#pragma once

namespace Durna
{
	class Window;

	class Application
	{
	public:
		Application();

		~Application();

		virtual void Init();

		virtual void Tick(float DeltaTime);

		void Shutdown();

		bool IsRunning() const;

	private:
		bool Running = true;
	};

}

