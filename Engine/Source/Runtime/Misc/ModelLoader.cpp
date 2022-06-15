#include "DurnaPCH.h"
#include "ModelLoader.h"
#include "Runtime/Engine/StaticMesh.h"
#include "Runtime/Math/Vector3.h"
#include "Runtime/Math/Vector2.h"
#include "Runtime/Math/Math.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "ThirdParty/TinyObjLoader/tiny_obj_loader.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"



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
					tinyobj::index_t idx = Shape.mesh.indices[(size_t)IndexOffset + v];

					tinyobj::real_t VX = attrib.vertices[(size_t)3 * idx.vertex_index + 0];
					tinyobj::real_t VY = attrib.vertices[(size_t)3 * idx.vertex_index + 1];
					tinyobj::real_t VZ = attrib.vertices[(size_t)3 * idx.vertex_index + 2];

					tinyobj::real_t TX = attrib.texcoords[(size_t)2 * idx.texcoord_index + 0];
					tinyobj::real_t TY = attrib.texcoords[(size_t)2 * idx.texcoord_index + 1];

					tinyobj::real_t NX = attrib.normals[(size_t)3 * idx.normal_index + 0];
					tinyobj::real_t NY = attrib.normals[(size_t)3 * idx.normal_index + 1];
					tinyobj::real_t NZ = attrib.normals[(size_t)3 * idx.normal_index + 2];

					tinyobj::real_t CX = attrib.colors[(size_t)3 * idx.vertex_index + 0];
					tinyobj::real_t CY = attrib.colors[(size_t)3 * idx.vertex_index + 1];
					tinyobj::real_t CZ = attrib.colors[(size_t)3 * idx.vertex_index + 2];

					Target->VertexPositions.push_back(VX);
					Target->VertexPositions.push_back(VY);
					Target->VertexPositions.push_back(VZ);

					Target->VertexUVs.push_back(TX);
					Target->VertexUVs.push_back(TY);

					Target->VertexNormals.push_back(NX);
					Target->VertexNormals.push_back(NY);
					Target->VertexNormals.push_back(NZ);

					Target->VertexColors.push_back(CX);
					Target->VertexColors.push_back(CY);
					Target->VertexColors.push_back(CZ);
					Target->VertexColors.push_back(1);

					Target->VertexIndices.push_back(IndexOffset + v);
				}

				IndexOffset += fv;
			}


			Target->VertexCount = int32(Target->VertexPositions.size() / 3);

			// calculate tangent and bionormal
			for (int32 i = 0; i < Target->VertexCount; i += 3)
			{
				Vector3f Pos1 = Vector3f(Target->VertexPositions[i * 3],
					Target->VertexPositions[i * 3 + 1], Target->VertexPositions[i * 3 + 2]);

				Vector3f Pos2 = Vector3f(Target->VertexPositions[(i + 1) * 3],
					Target->VertexPositions[(i + 1) * 3 + 1], Target->VertexPositions[(i + 2) * 3 + 2]);

				Vector3f Pos3 = Vector3f(Target->VertexPositions[(i + 2) * 3],
					Target->VertexPositions[(i + 2) * 3 + 1], Target->VertexPositions[(i + 2) * 3 + 2]);

				Vector3f Edge1 = Pos2 - Pos1;
				Vector3f Edge2 = Pos3 - Pos1;
				
				Vector2f UV1 = Vector2f(Target->VertexUVs[i * 2]		, Target->VertexUVs[i * 2 + 1]);
				Vector2f UV2 = Vector2f(Target->VertexUVs[(i + 1) * 2]	, Target->VertexUVs[(i + 1) * 2 + 1]);
				Vector2f UV3 = Vector2f(Target->VertexUVs[(i + 2) * 2]	, Target->VertexUVs[(i + 2) * 2 + 1]);

				Vector2f DeltaUVs1 = UV2 - UV1;
				Vector2f DeltaUVs2 = UV3 - UV1;

				float d = DeltaUVs1.X * DeltaUVs2.Y - DeltaUVs2.X * DeltaUVs1.Y;
				d = d != 0 ? d : SMALL_NUMBER;
				float f = 1.0f / d;

				Vector3f Tangent;
				Tangent.X = f * (DeltaUVs2.Y * Edge1.X - DeltaUVs1.Y * Edge2.X);
				Tangent.Y = f * (DeltaUVs2.Y * Edge1.Y - DeltaUVs1.Y * Edge2.Y);
				Tangent.Z = f * (DeltaUVs2.Y * Edge1.Z - DeltaUVs1.Y * Edge2.Z);
				Tangent = Tangent.Normalize();

				Vector3f Bionormal;
				Bionormal.X = f * (DeltaUVs2.X * Edge1.X + DeltaUVs1.X * Edge2.X);
				Bionormal.Y = f * (DeltaUVs2.X * Edge1.Y + DeltaUVs1.X * Edge2.Y);
				Bionormal.Z = f * (DeltaUVs2.X * Edge1.Z + DeltaUVs1.X * Edge2.Z);
				Bionormal = Bionormal.Normalize();

				auto PushVertexTangent = [&]()
				{
					Target->VertexTangents.push_back(Tangent.X);
					Target->VertexTangents.push_back(Tangent.Y);
					Target->VertexTangents.push_back(Tangent.Z);
				};

				PushVertexTangent();
				PushVertexTangent();
				PushVertexTangent();


				auto PushVertexBionormal = [&]()
				{
 					Target->VertexBionormals.push_back(Bionormal.X);
 					Target->VertexBionormals.push_back(Bionormal.Y);
 					Target->VertexBionormals.push_back(Bionormal.Z);
				};

				PushVertexBionormal();
				PushVertexBionormal();
				PushVertexBionormal();
			}
		}
		
	}

	void ModelLoader::TempLoad(const std::string& InPath, StaticMesh* Target)
	{
		Assimp::Importer importer;
		//const aiScene* scene = importer.ReadFile(InPath, aiProcess_Triangulate | aiProcess_FlipUVs);
		//const aiScene* scene = importer.ReadFile(InPath, aiProcess_Triangulate);
		//const aiScene* scene = importer.ReadFile(InPath, aiProcess_Triangulate | aiProcessPreset_TargetRealtime_MaxQuality);
		const aiScene* scene = importer.ReadFile(InPath, aiProcess_Triangulate);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}

		aiNode* Root = scene->mRootNode;

		if (Root && Root->mNumChildren > 0)
		{
			aiNode* Child = Root->mChildren[0];

			aiMesh* M = scene->mMeshes[Child->mMeshes[0]];

			if (M && Target)
			{
				std::cout << M->mNumVertices << std::endl;
				Target->VertexCount = M->mNumVertices;

				for (uint32 i = 0; i < M->mNumVertices; i++)
				{
					// position
					Target->VertexPositions.push_back(M->mVertices[i].x);
					Target->VertexPositions.push_back(M->mVertices[i].y);
					Target->VertexPositions.push_back(M->mVertices[i].z);

					// UVs
					Target->VertexUVs.push_back(M->mTextureCoords[0][i].x);
					Target->VertexUVs.push_back(M->mTextureCoords[0][i].y);

					// color
					uint32 ColorChannelNumber = M->GetNumColorChannels();

					if (ColorChannelNumber > 0)
						Target->VertexColors.push_back(M->mColors[0][i].r);
					if (ColorChannelNumber > 1)
						Target->VertexColors.push_back(M->mColors[0][i].g);
					if (ColorChannelNumber > 2)
						Target->VertexColors.push_back(M->mColors[0][i].b);
					if (ColorChannelNumber > 3)
						Target->VertexColors.push_back(M->mColors[0][i].a);

					// normal
					Target->VertexNormals.push_back(M->mNormals[i].x);
					Target->VertexNormals.push_back(M->mNormals[i].y);
					Target->VertexNormals.push_back(M->mNormals[i].z);

					// tangent
					Target->VertexTangents.push_back(M->mTangents[i].x);
					Target->VertexTangents.push_back(M->mTangents[i].y);
					Target->VertexTangents.push_back(M->mTangents[i].z);

					// biotanget
					Target->VertexBionormals.push_back(M->mBitangents[i].x);
					Target->VertexBionormals.push_back(M->mBitangents[i].y);
					Target->VertexBionormals.push_back(M->mBitangents[i].z);
				}

				// vertex indices
				for (uint32 i = 0; i < M->mNumFaces; i++)
				{
					aiFace f = M->mFaces[i];
					
					for(uint32 j = 0; j < f.mNumIndices; j++)
					{
						Target->VertexIndices.push_back(f.mIndices[j]);
					}
				}
			}

			else
			{
				std::cout << "No Mesh!\n";
			}
		}

		else
		{
			std::cout << "No ROot!\n";
		}
	}

}
