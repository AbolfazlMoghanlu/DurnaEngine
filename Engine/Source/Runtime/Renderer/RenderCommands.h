#pragma once

#include "Runtime/Components/PrimitiveComponent.h"

namespace Durna
{
	class Shader;

	class RenderCommands
	{
	public:
		RenderCommands();
		~RenderCommands();

		static void DrawPrimitive(PrimitiveComponent* Comp);

		

	private:
		
	};
}


