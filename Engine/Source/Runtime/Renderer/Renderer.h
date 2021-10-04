#pragma once

namespace Durna
{
	class Window;

	class Renderer
	{
	public:
		Renderer()
		{
		}

		static void Init();

		static void Shutdown();


	private:
		static Window* MainWindow;
	};
}



