#include "DurnaPCH.h"
#include "AssetLibrary.h"

#include "Runtime/Engine/BaseShapes.h"
#include "Runtime/Engine/StaticMesh.h"
#include "Runtime/Components/PrimitiveComponent.h"
#include "Runtime/Misc/ModelLoader.h"
#include "Runtime/Engine/Image/Image.h"
#include "Runtime/Renderer/Texture.h"
#include "Runtime/Renderer/Shader.h"
#include "Runtime/Renderer/Material.h"

namespace Durna
{
	StaticMesh* AssetLibrary::GizmoMesh;
	StaticMesh* AssetLibrary::RockMesh;
	StaticMesh* AssetLibrary::PlaneMesh;

	PrimitiveComponent* AssetLibrary::ScreenQuad;

	Image* AssetLibrary::TileImage;
	Image* AssetLibrary::WallImage;
	Image* AssetLibrary::SkyImage;
	Image* AssetLibrary::RgbImage;

	Image* AssetLibrary::Rock_Al_Image;
	Image* AssetLibrary::Rock_N_Image;
	Image* AssetLibrary::Rock_S_R_M_AO_Image;

	Image* AssetLibrary::WoodenFloor_Al_Image;
	Image* AssetLibrary::WoodenFloor_N_Image;
	Image* AssetLibrary::WoodenFloor_S_R_M_AO_Image;

	Texture* AssetLibrary::Rock_Al_Texture;
	Texture* AssetLibrary::Rock_N_Texture;
	Texture* AssetLibrary::Rock_S_R_M_AO_Texture;

	Texture* AssetLibrary::WoodenFloor_Al_Texture;
	Texture* AssetLibrary::WoodenFloor_N_Texture;
	Texture* AssetLibrary::WoodenFloor_S_R_M_AO_Texture;

	Texture* AssetLibrary::TileTexture;
	Texture* AssetLibrary::WallTexture;
	Texture* AssetLibrary::SkyTexture;

	Texture* AssetLibrary::RgbTexture;

	Shader* AssetLibrary::BaseShader;
	Shader* AssetLibrary::SkyShader;
	Shader* AssetLibrary::GizmoShader;
	Shader* AssetLibrary::PostProcessShader;
	Shader* AssetLibrary::RockShader;
	Shader* AssetLibrary::ResolvedShader;

	void AssetLibrary::Init()
	{
		GizmoMesh = new StaticMesh;
		ModelLoader::Load(Path::ModelRelativePath("Gizmo.obj"), GizmoMesh);

		RockMesh = new StaticMesh;
		ModelLoader::Load(Path::ModelRelativePath("SM_Rock.obj"), RockMesh);

		PlaneMesh = new StaticMesh;
		ModelLoader::Load(Path::ModelRelativePath("SM_Plane.obj"), PlaneMesh);

		ScreenQuad = new PrimitiveComponent("ScreenQuad");
		ScreenQuad->SetStaticMesh(&BaseShapes::Plane, 1);

		TileImage = new Image(Path::TextureRelativePath("T_TiledTexureCoordiante.png").c_str());
		WallImage = new Image(Path::TextureRelativePath("T_Wall.jpg").c_str());
		SkyImage = new Image(Path::TextureRelativePath("T_Sky.jpg").c_str());
		RgbImage = new Image(Path::TextureRelativePath("T_Rgb.png").c_str());

		Rock_Al_Image = new Image(Path::TextureRelativePath("T_Rock_Al.jpg").c_str());
		Rock_N_Image = new Image(Path::TextureRelativePath("T_Rock_N.jpg").c_str());
		Rock_S_R_M_AO_Image = new Image(Path::TextureRelativePath("T_Rock_S_R_M_AO.png").c_str());

		WoodenFloor_Al_Image = new Image(Path::TextureRelativePath("T_WoodenFloor_Al.jpg").c_str());
		WoodenFloor_N_Image = new Image(Path::TextureRelativePath("T_WoodenFloor_N.jpg").c_str());
		WoodenFloor_S_R_M_AO_Image = new Image(Path::TextureRelativePath("T_WoodenFloor_S_R_M_A.png").c_str());
			

		TileTexture = new Texture(TileImage);
		WallTexture = new Texture(WallImage);
		SkyTexture = new Texture(SkyImage);
		RgbTexture = new Texture(RgbImage);

		Rock_Al_Texture = new Texture(Rock_Al_Image);
		Rock_N_Texture = new Texture(Rock_N_Image);
		Rock_S_R_M_AO_Texture = new Texture(Rock_S_R_M_AO_Image);

		WoodenFloor_Al_Texture = new Texture(WoodenFloor_Al_Image);
		WoodenFloor_N_Texture = new Texture(WoodenFloor_N_Image);
		WoodenFloor_S_R_M_AO_Texture = new Texture(WoodenFloor_S_R_M_AO_Image);

		BaseShader = new Shader(Path::ShaderRelativePath("BaseShader.glsl"));
		SkyShader = new Shader(Path::ShaderRelativePath("SkySphere.glsl"));
		GizmoShader = new Shader(Path::ShaderRelativePath("Gizmo.glsl"));
		PostProcessShader = new Shader(Path::ShaderRelativePath("PostProcess.glsl"));
		RockShader = new Shader(Path::ShaderRelativePath("RockShader.glsl"));
		ResolvedShader = new Shader(Path::ShaderRelativePath("ResolvedShader.glsl"));
	}
}
