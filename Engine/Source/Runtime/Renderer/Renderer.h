#pragma once

#include "Runtime/Math/Vector3.h"

namespace Durna
{
	class Window;

	// TODO: Remove
	class PrimitiveComponent;

	class Renderer
	{
	public:
		Renderer();

		static void Init();

		static void Tick(float DeltaTime);

		static void Shutdown();

		static Window* MainWindow;

		// TODO: Remove
		 static PrimitiveComponent* pr;

		 static float Time;

		 static Vector3f PrLocation;
	};
}



