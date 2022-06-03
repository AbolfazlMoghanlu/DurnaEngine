#pragma once

#include "Runtime/Components/PrimitiveComponent.h"
#include "Runtime/Math/LinearColor.h"
#include "Runtime/Math/ViewMatrix.h"

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
		static void DrawPrimitive(PrimitiveComponent* Comp, const ViewMatrix<float>& InViewMatrix);


		static void DrawFrameBufferToScreen(FrameBuffer* InFrameBuffer, Material* InMaterial);

		static void EnableDepthTest();
		static void DisableDepthTest();

		static void SetClearColor(const LinearColor& ClearColor);

		static void EnableBackFaceCulling();
		static void DisableBackFaceCulling();

		static void EnableStencilTest();
		static void DisableStencilTest();

		static void SetStencilOperationReplace();

		static void ClearColorBuffer();
		static void ClearDepthBuffer();
		static void ClearStencilBuffer();

		static void SetDrawWireframe();

		static void SetViewportSize(const IntPoint& Size, const IntPoint& Offset = IntPoint::Zero);
	};
}


