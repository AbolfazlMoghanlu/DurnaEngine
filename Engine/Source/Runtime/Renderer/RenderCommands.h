#pragma once

#include "Runtime/Components/PrimitiveComponent.h"

namespace Durna
{
	class RenderCommands
	{
	public:
		RenderCommands();
		~RenderCommands();

		static void DrawPrimitive(PrimitiveComponent& Comp);


	private:

	};
}


