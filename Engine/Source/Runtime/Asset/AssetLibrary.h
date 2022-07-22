#pragma once

namespace Durna
{
	class StaticMesh;
	class PrimitiveComponent;
	class Image;
	class Texture2D;
	class TextureCube;
	class Shader;
	class Material;

	//temporally class for handling test assets
	struct AssetLibrary
	{
		static void Init();

		static StaticMesh* FlipedSphere;
		static StaticMesh* Sphere;
		static StaticMesh* GizmoMesh;
		static StaticMesh* RockMesh;
		static StaticMesh* PlaneMesh;
		static StaticMesh* ArrowMesh;

		static PrimitiveComponent* ScreenQuad;
		static PrimitiveComponent* PointLightSphere;

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
		
		static Image* SkyCubemap_Top;
		static Image* SkyCubemap_Bottom;
		static Image* SkyCubemap_Right;
		static Image* SkyCubemap_Left;
		static Image* SkyCubemap_Front;
		static Image* SkyCubemap_Back;

		static Image* DirectionalLightIconImage;
		static Image* SkyLightIconImage;


		static Texture2D* Rock_Al_Texture;
		static Texture2D* Rock_N_Texture;
		static Texture2D* Rock_S_R_M_AO_Texture;
					  
		static Texture2D* WoodenFloor_Al_Texture;
		static Texture2D* WoodenFloor_N_Texture;
		static Texture2D* WoodenFloor_S_R_M_AO_Texture;
					  
		static Texture2D* TileTexture;
		static Texture2D* WallTexture;
		static Texture2D* SkyTexture;
		static Texture2D* RgbTexture;

		static TextureCube* SkyCubemapTexture;

		static Texture2D* DirectionalLightIconTexture;
		static Texture2D* SkyLightIconTexture;
		
		static Shader* BaseShader;
		static Shader* SkyShader;
		static Shader* GizmoShader;
		static Shader* PostProcessShader;
		static Shader* RockShader;
		static Shader* ResolvedShader;
		static Shader* ShadowmapShader;
		static Shader* PointLightShader;
		static Shader* ArrowShader;
		static Shader* BillboardShader;
		static Shader* BasepassShader;
	};
}