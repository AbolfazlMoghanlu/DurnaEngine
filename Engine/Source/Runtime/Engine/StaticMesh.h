#pragma once
namespace Durna
{
	class StaticMesh
	{
	public:
		StaticMesh();

		StaticMesh(const std::vector<float>& InVertexPositions,
			const std::vector<uint32>& InVertexIndices,
			const std::vector<float>& InUVs,
			const std::vector<float>& InNormals,
			const std::vector<float>& InVertexColor);
			
		~StaticMesh();

	public:
		/*
		 * List of vertex relative positions.
		 * Size should be multiplication of 3
		 */
		std::vector<float> VertexPositions;

		std::vector<uint32> VertexIndices;

		/*
		 * List of vertex UVs.
		 * Size should be multiplication of 2
		 */
		std::vector<float> VertexUVs;

		/*
		 * List of vertex Normals.
		 * Size should be multiplication of 3
		 */
		std::vector<float> VertexNormal;

		/*
		 * List of vertex colors.
		 * Size should be multiplication of 4
		 */
		std::vector<float> VertexColors;

		int VertexCount;
	};
}