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

		static void Tick(float DeltaTime);

		static void Shutdown();

		static Window* MainWindow;
	};
}



