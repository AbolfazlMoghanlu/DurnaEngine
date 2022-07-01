#include "DurnaPCH.h"
#include "ModelLoader.h"
#include "Runtime/Engine/StaticMesh.h"
#include "Runtime/Math/Vector3.h"
#include "Runtime/Math/Vector2.h"
#include "Runtime/Math/Math.h"
#include "Runtime/Misc/Assert.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

LOG_DEFINE_CATEGORY(LogModelLoader, "ModelLoader");

namespace Durna
{
	void ModelLoader::Load(const std::string& InPath, StaticMesh* Target, bool bFlipUVs,
		bool bGenSmoothNormal, bool bGenTangent, float Scale)
	{
		if (!Target)
		{
			LOG(LogModelLoader, Error, "Please specify target for loading \"%s\".", InPath.c_str());
			return;
		}

		Assimp::Importer importer;

		uint32 ImportFlags = aiProcess_Triangulate | aiProcessPreset_TargetRealtime_MaxQuality;

		if (bFlipUVs)
			ImportFlags |= aiProcess_FlipUVs;

		if (!bGenSmoothNormal)
			ImportFlags &= ~aiProcess_GenSmoothNormals;

		if (!bGenTangent)
		{
			ImportFlags &= ~aiProcess_CalcTangentSpace;
		}

		const aiScene* scene = importer.ReadFile(InPath, ImportFlags);


		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG(LogModelLoader, Error, "Failed to load \"%s\", do to bad scene.", InPath.c_str());
			return;
		}

		aiNode* Root = scene->mRootNode;

		if (Root && Root->mNumChildren > 0)
		{
			aiNode* Child = Root->mChildren[0];

			aiMesh* M = scene->mMeshes[Child->mMeshes[0]];

			if (M)
			{
				ensure(M->HasTangentsAndBitangents(), 
					"\"%s\" doesn't have tangents, please enable gentangent import option.", InPath.c_str());

				Target->VertexCount = M->mNumVertices;

				for (uint32 i = 0; i < M->mNumVertices; i++)
				{
					// position
					Target->VertexPositions.push_back(M->mVertices[i].x * Scale);
					Target->VertexPositions.push_back(M->mVertices[i].y * Scale);
					Target->VertexPositions.push_back(M->mVertices[i].z * Scale);

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
				LOG(LogModelLoader, Error, "Couldn't find mesh in \"%s\".", InPath.c_str());
				return;
			}
		}

		else
		{
			LOG(LogModelLoader, Error, "Couldn't find root node in \"%s\".", InPath.c_str());
			return;
		}
	}
}
