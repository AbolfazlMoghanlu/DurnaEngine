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


	StaticMesh BaseShapes::Cube(
		// position
		{
			// top
			-0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			// bottom
			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f
		},

		// indices
		{
			// top
			0, 1, 2,
			0, 2, 3,

			// bottom
			4, 6, 5,
			4, 7, 6,

			// front
			2, 1, 5,
			2, 5, 6,

			// back
			0, 3, 7,
			0, 7, 4,

			// right
			1, 0, 4,
			1, 4, 5,

			// left
			3, 2, 6,
			3, 6, 7
		},
		{},
		{},

		// vertex colors
		{
			1, 0, 0, 1,
			0, 1, 0, 1,
			0, 0, 1, 1,
			0, 0, 0, 0,
			1, 0, 0, 1,
			0, 1, 0, 1,
			0, 0, 1, 1,
			0, 0, 0, 0
		}
	);
}