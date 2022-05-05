#pragma once

namespace Durna
{
	class StaticMesh;
	class Image;
	class Texture;
	class Shader;
	class Material;

	//temporally class for handling test assets
	struct AssetLibrary
	{
		static void Init();

		static StaticMesh* GizmoMesh;

		static Image* TileImage;
		static Image* WallImage;
		static Image* SkyImage;
		static Image* RgbImage;
		
		static Texture* TileTexture;
		static Texture* WallTexture;
		static Texture* SkyTexture;
		static Texture* RgbTexture;
		
		static Shader* BaseShader;
		static Shader* SkyShader;
		static Shader* GizmoShader;
		
		static Material* BaseMaterial;
		static Material* SkyMaterial;
		static Material* GizmoMaterial;
	};
}

