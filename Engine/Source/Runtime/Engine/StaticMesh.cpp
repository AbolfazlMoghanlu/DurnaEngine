#include "DurnaPCH.h"
#include "StaticMesh.h"

namespace Durna
{
	StaticMesh::StaticMesh(const std::vector<float>& InVertexPositions, const std::vector<uint32>& InVertexIndices,
		const std::vector<float>& InUVs, const std::vector<float>& InNormals, const std::vector<float>& InVertexColor)
		: VertexPositions(InVertexPositions)
		, VertexIndices(InVertexIndices)
		, VertexUVs(InUVs)
		, VertexNormals(InNormals)
		, VertexColors(InVertexColor)
	{
		VertexCount = (uint32)(InVertexPositions.size() / 3);
	}

	StaticMesh::StaticMesh()
	{

	}

	StaticMesh::~StaticMesh()
	{

	}
}