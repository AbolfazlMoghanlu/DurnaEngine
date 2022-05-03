#include "DurnaPCH.h"
#include "ModelLoader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "ThirdParty/TinyObjLoader/tiny_obj_loader.h"

namespace Durna
{
	void ModelLoader::Load(const std::string& InPath)
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
			std::cout << shapes[0].name << std::endl;
		}
		
	}

}
