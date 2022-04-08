#pragma once

#include "Runtime/Math/Vector3.h"
#include "Runtime/Math/Vector2.h"
#include "Runtime/Math/Color.h"

#define MAX_TEXCOORDS 4

namespace Durna
{
	struct StaticMeshBuildVertex
	{
		Vector3f Position;

		Vector3f TangentX;
		Vector3f TangentY;
		Vector3f TangetZ;

		Vector2f UVs[MAX_TEXCOORDS];
		Color VColor;
	};

	class Components
	{
		
	};
}


