#include "DurnaPCH.h"
#include "ModelLoader.h"
#include "Runtime/Engine/StaticMesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "ThirdParty/TinyObjLoader/tiny_obj_loader.h"

namespace Durna
{
	void ModelLoader::Load(const std::string& InPath, StaticMesh* Target)
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		bool bSuccess = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, InPath.c_str());

		if (!bSuccess)
		{ 
			std::cout << "failed";
		}

		if (shapes.size() > 0)
		{
			const auto& Shape = shapes[0];

			int32 IndexOffset = 0;
			for (int32 f = 0; f < Shape.mesh.num_face_vertices.size(); f++)
			{
				int32 fv = int32(Shape.mesh.num_face_vertices[0]);

				for (int32 v = 0; v < fv; v++)
				{
					tinyobj::index_t idx = Shape.mesh.indices[IndexOffset + v];

					tinyobj::real_t VX = attrib.vertices[3 * idx.vertex_index + 0];
					tinyobj::real_t VY = attrib.vertices[3 * idx.vertex_index + 1];
					tinyobj::real_t VZ = attrib.vertices[3 * idx.vertex_index + 2];

					tinyobj::real_t TX = attrib.texcoords[2 * idx.texcoord_index + 0];
					tinyobj::real_t TY = attrib.texcoords[2 * idx.texcoord_index + 1];

					tinyobj::real_t NX = attrib.normals[3 * idx.normal_index + 0];
					tinyobj::real_t NY = attrib.normals[3 * idx.normal_index + 1];
					tinyobj::real_t NZ = attrib.normals[3 * idx.normal_index + 2];

					Target->VertexPositions.push_back(VX);
					Target->VertexPositions.push_back(VY);
					Target->VertexPositions.push_back(VZ);

					Target->VertexUVs.push_back(TX);
					Target->VertexUVs.push_back(TY);

					Target->VertexNormal.push_back(NX);
					Target->VertexNormal.push_back(NY);
					Target->VertexNormal.push_back(NZ);

					Target->VertexIndices.push_back(IndexOffset + v);
				}

				IndexOffset += fv;
			}


			Target->VertexCount = Target->VertexPositions.size() / 3;

			for (int32 i = 0; i < Target->VertexCount * 4; i++)
			{
				Target->VertexColors.push_back(1);
			}


		}
		
	}

}
