#pragma once

#include "Runtime/Components/PrimitiveComponent.h"
#include "Runtime/Math/LinearColor.h"

namespace Durna
{
	class Shader;

	class RenderCommands
	{
	public:
		RenderCommands();
		~RenderCommands();

		static void DrawPrimitive(PrimitiveComponent* Comp);

		static void EnableDepthTest();
		static void DisableDepthTest();

		static void SetClearColor(const LinearColor& ClearColor);

		static void EnableBackFaceCulling();
		static void DisableBackFaceCulling();

	private:
		
	};
}


