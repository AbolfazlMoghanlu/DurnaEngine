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
		static StaticMesh* RockMesh;
		static StaticMesh* PlaneMesh;

		static PrimitiveComponent* ScreenQuad;

		static Image* TileImage;
		static Image* WallImage;
		static Image* SkyImage;
		static Image* RgbImage;

		static Image* Rock_Al_Image;
		static Image* Rock_N_Image;
		static Image* Rock_S_R_M_AO_Image;

		static Image* WoodenFloor_Al_Image;
		static Image* WoodenFloor_N_Image;
		static Image* WoodenFloor_S_R_M_AO_Image;

		static Texture* Rock_Al_Texture;
		static Texture* Rock_N_Texture;
		static Texture* Rock_S_R_M_AO_Texture;
		
		static Texture* WoodenFloor_Al_Texture;
		static Texture* WoodenFloor_N_Texture;
		static Texture* WoodenFloor_S_R_M_AO_Texture;

		static Texture* TileTexture;
		static Texture* WallTexture;
		static Texture* SkyTexture;
		static Texture* RgbTexture;
		
		static Shader* BaseShader;
		static Shader* SkyShader;
		static Shader* GizmoShader;
		static Shader* PostProcessShader;
		static Shader* RockShader;
		static Shader* ResolvedShader;
	};
}