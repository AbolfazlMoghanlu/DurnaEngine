#pragma once

#include "Runtime/Math/Vector3.h"

namespace Durna
{
	class Window;

	class Renderer
	{
	public:
		Renderer();
		virtual ~Renderer();

		static void Init();

		static void Tick(float DeltaTime);

		static void Shutdown();

		static Window* GetWindow();
		static float GetTime();

	private:
		static std::unique_ptr<Window> MainWindow;
		static float Time;
	};
}



