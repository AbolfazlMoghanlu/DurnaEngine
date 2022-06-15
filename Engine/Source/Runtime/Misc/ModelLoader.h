#pragma once

namespace Durna
{
	class StaticMesh;

	class ModelLoader
	{
	public:
		static void Load(const std::string& InPath, StaticMesh* Target,
			bool bFlipUVs = false, bool bGenSmoothNormal = false, bool bGenTangent = false, 
			float Scale = 1.0f);
	};

}

