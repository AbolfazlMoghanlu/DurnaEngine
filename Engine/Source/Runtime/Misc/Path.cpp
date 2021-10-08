#include "DurnaPCH.h"
#include "Path.h"

namespace Durna
{
	std::string Path::ShaderPath = "../Content/Shader/";
		
	std::string Path::ShaderRelativePath(const std::string& RelativePath)
	{
		return ShaderPath + RelativePath;
	}
}


