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
		 * Size should be multiplication of 3
		 */
		std::vector<float> VertexPositions;

		std::vector<uint32> VertexIndices;

		/*
		 * Size should be multiplication of 2
		 */
		std::vector<float> VertexUVs;

		/*
		 * Size should be multiplication of 3
		 */
		std::vector<float> VertexNormals;

		/*
		 * Size should be multiplication of 3
		 */
		std::vector<float> VertexTangents;

		/*
		 * Size should be multiplication of 3
		 */
		std::vector<float> VertexBionormals;


		/*
		 * Size should be multiplication of 4
		 */
		std::vector<float> VertexColors;

		int32 VertexCount = 0;
	};
}