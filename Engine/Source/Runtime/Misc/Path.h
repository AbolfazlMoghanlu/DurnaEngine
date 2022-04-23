#pragma once

namespace Durna
{
	class Path
	{
	public:
		static std::string ShaderRelativePath(const std::string& RelativePath);
		static std::string TextureRelativePath(const std::string& RelativePath);

	public:
		static std::string ShaderPath;
		static std::string TexturePath;
	};

}

