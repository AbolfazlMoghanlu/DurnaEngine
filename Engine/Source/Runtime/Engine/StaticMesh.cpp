#include "DurnaPCH.h"
#include "StaticMesh.h"

namespace Durna
{



	

	StaticMesh::StaticMesh(const std::vector<float>& InVertexPositions, const std::vector<int>& InVertexIndices,
		const std::vector<float>& InUVs, const std::vector<float>& InNormals, const std::vector<float>& InVertexColor)
		: VertexPositions(InVertexPositions)
		, VertexIndices(InVertexIndices)
		, VertexUVs(InUVs)
		, VertexNormal(InNormals)
		, VertexColors(InVertexColor)
	{
		VertexCount = (int)(InVertexPositions.size() / 3);
	}

	StaticMesh::~StaticMesh()
	{

	}

}