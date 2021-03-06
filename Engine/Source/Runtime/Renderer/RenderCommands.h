#pragma once

#include "Runtime/Components/PrimitiveComponent.h"
#include "Runtime/Math/LinearColor.h"
#include "Runtime/Math/ViewMatrix.h"
#include "Runtime/Math/OrthoMatrix.h"

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
		static void DrawPrimitive(PrimitiveComponent* Comp, const Matrix<float>& InViewMatrix, const Matrix<float>& InOrthu);


		static void DrawFrameBufferToScreen(FrameBuffer* InFrameBuffer, Material* InMaterial);
		static void DrawFrameBufferToScreen(FrameBuffer* InFrameBuffer, Shader* InShader);

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


