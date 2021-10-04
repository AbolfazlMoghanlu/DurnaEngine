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

		void Shutdown();

		bool IsRunning() const;

	private:
		bool Running = true;
	};

}

