#pragma once

#include "Runtime/Math/Vector3.h"
#include "Runtime/Renderer/Material.h"
#include "Runtime/Renderer/PostProcessSetting.h"

namespace Durna
{
	class Window;

	class StaticMeshActor;
	class PrimitiveComponent;
	class FrameBuffer;
	class RenderQueue;
	class GBuffer;

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

		static void RegisterToRenderQueue(PrimitiveComponent* Pr);

		static Material PostProccessMaterial;

		static PostProcessSetting PPSetting;

	protected:
		

	private:
		static std::unique_ptr<Window> MainWindow;
		static float Time;

		static std::shared_ptr<GBuffer> Gbuffer;
		static RenderQueue RenderQue;

		static void UpdatePostProcessUniforms();

		static uint32 framebuffer;
		static uint32 textureColorbuffer;
		static uint32 textureDepth;
		static uint32 textured;
		static uint32 textures;
	};
}