#include "DurnaPCH.h"
#include "ModelLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Durna
{
	void ModelLoader::Load(const std::string& InPath)
	{
		Assimp::Importer Importer;
		const aiScene* Scene = Importer.ReadFile(InPath, aiProcess_Triangulate | aiProcess_FlipUVs);


	}

}
