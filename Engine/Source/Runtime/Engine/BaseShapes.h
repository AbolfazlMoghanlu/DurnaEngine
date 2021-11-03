#pragma once

#include "Runtime/Engine/StaticMesh.h"

class StaticMesh;

namespace Durna
{
	class BaseShapes
	{
	public:
		BaseShapes();
		~BaseShapes();

		static StaticMesh Plane;
		static StaticMesh Cube;
	};
}

