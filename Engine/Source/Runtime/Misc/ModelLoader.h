#pragma once

namespace Durna
{
	class StaticMesh;

	class ModelLoader
	{
	public:
		static void Load(const std::string& InPath, StaticMesh* Target);

		static void TempLoad(const std::string& InPath, StaticMesh* Target);

	};

}

