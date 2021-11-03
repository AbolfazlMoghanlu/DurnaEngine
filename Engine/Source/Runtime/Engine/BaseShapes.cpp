#include "DurnaPCH.h"
#include "BaseShapes.h"

#include "Runtime/Engine/StaticMesh.h"

namespace Durna
{
	BaseShapes::BaseShapes()
	{

	}

	BaseShapes::~BaseShapes()
	{

	}

	StaticMesh BaseShapes::Plane(

		// vertex positions
		{
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left
		},

		// indices
		{
			0, 1, 3,
			1, 2, 3
		},

		// uvs
		{
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f
		},

		// normals
		{
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f
		},

		// vertex colors
		std::vector<float>(16, 1.0f)
	);

	
	//StaticMesh BaseShapes::Cube;

}