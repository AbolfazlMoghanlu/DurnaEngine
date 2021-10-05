#pragma once

namespace Durna
{
	class Window;

	class Application
	{
	public:
		Application()
		{
		}

		void Init();

		void Tick(float DeltaTime);

		void Shutdown();

		bool IsRunning() const;

	private:
		bool Running = true;
	};

}

