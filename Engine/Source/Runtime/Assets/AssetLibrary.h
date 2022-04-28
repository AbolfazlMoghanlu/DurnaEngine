#pragma once

namespace Durna
{
	class Image;
	class Texture;
	class Shader;
	class Material;

	//temporally class for handling test assets
	struct AssetLibrary
	{
		static void Init();

		static Image* TileImage;
		static Image* WallImage;
		
		static Texture* TileTexture;
		static Texture* WallTexture;
		
		static Shader* BaseShader;
		
		static Material* BaseMaterial;
	};
}

