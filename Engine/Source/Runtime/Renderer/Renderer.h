#pragma once

#include "Runtime/Math/Vector3.h"
#include "Runtime/Math/Rotator.h"
#include "Runtime/Renderer/Material.h"
#include "Runtime/Renderer/PostProcessSetting.h"
#include "Runtime/Renderer/RenderTypes.h"

namespace Durna
{
	class Window;

	class StaticMeshActor;
	class PrimitiveComponent;
	class FrameBuffer;
	class RenderQueue;
	class GBuffer;
	class ResolveDefferedBuffer;
	class ShadowFrameBuffer;

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

		static void OnResolutionChanged(const IntPoint& InResolution);
		static void ResizeBuffers(const IntPoint& InResolution);

		static void RegisterToRenderQueue(PrimitiveComponent* Pr);

		static Material PostProccessMaterial;
		static Material ResolvedMaterial;

		static PostProcessSetting PPSetting;

		static LinearColor AmbientLightColor;
		static float AmbientLightIntensity;

		// TODO: make private
		static std::shared_ptr<GBuffer> Gbuffer;


	private:
		static void Render();
		
		static void BeginRenderGBuffer();
		static void RenderGBuffer();
		static void FinishRenderGBuffer();

		static void RenderShadowBuffers();

		static std::shared_ptr<Window> MainWindow;
		static float Time;

		static RenderQueue RenderQue;

		static void UpdatePostProcessUniforms();
	};
}