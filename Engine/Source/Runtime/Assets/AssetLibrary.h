#pragma once

namespace Durna
{
	class StaticMesh;
	class PrimitiveComponent;
	class Image;
	class Texture;
	class Shader;
	class Material;

	//temporally class for handling test assets
	struct AssetLibrary
	{
		static void Init();

		static StaticMesh* GizmoMesh;

		static PrimitiveComponent* ScreenQuad;

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
		static Shader* PP;
	};
}

