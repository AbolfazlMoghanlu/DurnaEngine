#pragma once

namespace Durna
{
	class StaticMesh;

	class ModelLoader
	{
	public:
		static void Load(const std::string& InPath, StaticMesh* Target);

	};

}

