#pragma once

#include "Runtime/Math/Vector3.h"

namespace Durna
{
	class Window;

	class StaticMeshActor;

	class FrameBuffer;

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

		static void OnResizeWindow(int32 InWidth, int32 InHeight);

	private:
		static std::unique_ptr<Window> MainWindow;
		static float Time;
		static StaticMeshActor* PlaneActor;

		static std::shared_ptr<FrameBuffer> GBuffer;
	};
}