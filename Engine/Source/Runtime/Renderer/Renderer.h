#pragma once

#include "Runtime/Math/Vector3.h"

namespace Durna
{
	class Window;

	// TODO: Remove
	class PrimitiveComponent;

	class Actor;

	class Renderer
	{
	public:
		Renderer();

		static void Init();

		static void Tick(float DeltaTime);

		static void Shutdown();

		static Window* GetWindow();
		static float GetTime();

	private:
		static Window* MainWindow;
		static float Time;
	};
}



