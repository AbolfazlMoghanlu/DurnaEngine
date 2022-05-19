#pragma once

#include "Runtime/Components/PrimitiveComponent.h"
#include "Runtime/Math/LinearColor.h"

namespace Durna
{
	class Material;
	class Shader;
	class FrameBuffer;

	class RenderCommands
	{
	public:
		RenderCommands();
		~RenderCommands();

		static void DrawPrimitive(PrimitiveComponent* Comp);
		static void DrawFrameBufferToScreen(FrameBuffer* InFrameBuffer, Material* InMaterial);

		static void EnableDepthTest();
		static void DisableDepthTest();

		static void SetClearColor(const LinearColor& ClearColor);

		static void EnableBackFaceCulling();
		static void DisableBackFaceCulling();

		static void ClearColorBuffer();
		static void ClearDepthBuffer();

		static void SetDrawWireframe();

	private:
		
	};
}


