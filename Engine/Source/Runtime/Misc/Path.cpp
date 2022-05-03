#include "DurnaPCH.h"
#include "Path.h"

namespace Durna
{
	std::string Path::ShaderPath = "../Content/Shader/";
	std::string Path::TexturePath = "../Content/Texture/";
	std::string Path::ModelPath = "../Content/Model/";

	std::string Path::ShaderRelativePath(const std::string& RelativePath)
	{
		return ShaderPath + RelativePath;
	}

	std::string Path::TextureRelativePath(const std::string& RelativePath)
	{
		return TexturePath + RelativePath;
	}

	std::string Path::ModelRelativePath(const std::string& RelativePath)
	{
		return ModelPath + RelativePath;
	}

}


