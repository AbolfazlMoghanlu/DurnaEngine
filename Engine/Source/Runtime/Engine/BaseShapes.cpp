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
			 1.0f,  1.0f, 0.0f,  // top right
			 1.0f, -1.0f, 0.0f,  // bottom right
			-1.0f, -1.0f, 0.0f,  // bottom left
			-1.0f,  1.0f, 0.0f   // top left
		},

		// indices
		{
			0, 1, 3,
			1, 2, 3
		},
	

		// uvs
		{
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f
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
			// Front face
			-1.0, -1.0,  1.0,
			 1.0, -1.0,  1.0,
			 1.0,  1.0,  1.0,
			-1.0,  1.0,  1.0,

			// Back face
			-1.0, -1.0, -1.0,
			-1.0,  1.0, -1.0,
			 1.0,  1.0, -1.0,
			 1.0, -1.0, -1.0,

			 // Top face
			 -1.0,  1.0, -1.0,
			 -1.0,  1.0,  1.0,
			  1.0,  1.0,  1.0,
			  1.0,  1.0, -1.0,

			  // Bottom face
			  -1.0, -1.0, -1.0,
			   1.0, -1.0, -1.0,
			   1.0, -1.0,  1.0,
			  -1.0, -1.0,  1.0,

			  // Right face
			   1.0, -1.0, -1.0,
			   1.0,  1.0, -1.0,
			   1.0,  1.0,  1.0,
			   1.0, -1.0,  1.0,

			   // Left face
			   -1.0, -1.0, -1.0,
			   -1.0, -1.0,  1.0,
			   -1.0,  1.0,  1.0,
			   -1.0,  1.0, -1.0,
		},

		// indices
		{
			0,  1,  2,      0,  2,  3,    // front
			4,  5,  6,      4,  6,  7,    // back
			8,  9,  10,     8,  10, 11,   // top
			12, 13, 14,     12, 14, 15,   // bottom
			16, 17, 18,     16, 18, 19,   // right
			20, 21, 22,     20, 22, 23,   // left
		},

		// UVs
		{
			// top
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			// bottom
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			// front
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			// back
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			// right
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			// left
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
		},

		// Normals #junk
		{
			1, 0, 0,
			0, 1, 0,
			0, 0, 1,
			0, 0, 0,
			1, 0, 0,
			0, 1, 0,
			0, 0, 1,
			0, 0, 0,
			1, 0, 0,
			0, 1, 0,
			0, 0, 1,
			0, 0, 0,
			1, 0, 0,
			0, 1, 0,
			0, 0, 1,
			0, 0, 0,
			1, 0, 0,
			0, 1, 0,
			0, 0, 1,
			0, 0, 0,
			1, 0, 0,
			0, 1, 0,
			0, 0, 1,
			0, 0, 0
		},

		// vertex colors
		{
			1, 0, 0, 1,
			0, 1, 0, 1,
			0, 0, 1, 1,
			0, 0, 0, 0,
			1, 0, 0, 1,
			0, 1, 0, 1,
			0, 0, 1, 1,
			0, 0, 0, 0,
			1, 0, 0, 1,
			0, 1, 0, 1,
			0, 0, 1, 1,
			0, 0, 0, 0,
			1, 0, 0, 1,
			0, 1, 0, 1,
			0, 0, 1, 1,
			0, 0, 0, 0,
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