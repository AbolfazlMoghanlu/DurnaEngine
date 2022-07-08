#include "DurnaPCH.h"
#include "AssetLibrary.h"

#include "Runtime/Engine/BaseShapes.h"
#include "Runtime/Engine/StaticMesh.h"
#include "Runtime/Components/PrimitiveComponent.h"
#include "Runtime/Misc/ModelLoader.h"
#include "Runtime/Engine/Image/Image.h"
#include "Runtime/Renderer/Texture.h"
#include "Runtime/Renderer/Texture2D.h"
#include "Runtime/Renderer/TextureCube.h"
#include "Runtime/Renderer/Shader.h"
#include "Runtime/Renderer/Material.h"

namespace Durna
{
	StaticMesh* AssetLibrary::FlipedSphere;
	StaticMesh* AssetLibrary::Sphere;

	StaticMesh* AssetLibrary::GizmoMesh;
	StaticMesh* AssetLibrary::RockMesh;

	StaticMesh* AssetLibrary::PlaneMesh;
	StaticMesh* AssetLibrary::ArrowMesh;

	PrimitiveComponent* AssetLibrary::ScreenQuad;
	PrimitiveComponent* AssetLibrary::PointLightSphere;

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

	Image* AssetLibrary::SkyCubemap_Top;
	Image* AssetLibrary::SkyCubemap_Bottom;
	Image* AssetLibrary::SkyCubemap_Right;
	Image* AssetLibrary::SkyCubemap_Left;
	Image* AssetLibrary::SkyCubemap_Front;
	Image* AssetLibrary::SkyCubemap_Back;

	Image* AssetLibrary::DirectionalLightIconImage;
	Image* AssetLibrary::SkyLightIconImage;

	Texture2D* AssetLibrary::Rock_Al_Texture;
	Texture2D* AssetLibrary::Rock_N_Texture;
	Texture2D* AssetLibrary::Rock_S_R_M_AO_Texture;
		   
	Texture2D* AssetLibrary::WoodenFloor_Al_Texture;
	Texture2D* AssetLibrary::WoodenFloor_N_Texture;
	Texture2D* AssetLibrary::WoodenFloor_S_R_M_AO_Texture;
		   
	Texture2D* AssetLibrary::TileTexture;
	Texture2D* AssetLibrary::WallTexture;
	Texture2D* AssetLibrary::SkyTexture;
		   
	Texture2D* AssetLibrary::RgbTexture;

	TextureCube* AssetLibrary::SkyCubemapTexture;

	Texture2D* AssetLibrary::DirectionalLightIconTexture;
	Texture2D* AssetLibrary::SkyLightIconTexture;

	Shader* AssetLibrary::BaseShader;
	Shader* AssetLibrary::SkyShader;
	Shader* AssetLibrary::GizmoShader;
	Shader* AssetLibrary::PostProcessShader;
	Shader* AssetLibrary::RockShader;
	Shader* AssetLibrary::ResolvedShader;
	Shader* AssetLibrary::ShadowmapShader;
	Shader* AssetLibrary::PointLightShader;

	Shader* AssetLibrary::ArrowShader;
	Shader* AssetLibrary::BillboardShader;
	Shader* AssetLibrary::BasepassShader;

	void AssetLibrary::Init()
	{
		FlipedSphere = new StaticMesh;
		ModelLoader::Load(Path::ModelRelativePath("FlipedSphere.obj"), FlipedSphere, 0, 0, 1);
		
		Sphere = new StaticMesh;
		ModelLoader::Load(Path::ModelRelativePath("Sphere.obj"), Sphere, 0, 0, 1);

		GizmoMesh = new StaticMesh;
		ModelLoader::Load(Path::ModelRelativePath("Gizmo.obj"), GizmoMesh, 0, 0, 1);

		RockMesh = new StaticMesh;
		ModelLoader::Load(Path::ModelRelativePath("SM_Rock.fbx"), RockMesh, 0, 0, 1, 0.01f);

		PlaneMesh = new StaticMesh;
		ModelLoader::Load(Path::ModelRelativePath("SM_Plane.obj"), PlaneMesh, 0, 0, 1);	 
		
		ArrowMesh = new StaticMesh;
		ModelLoader::Load(Path::ModelRelativePath("Arrow.obj"), ArrowMesh, 0, 0, 1);

		ScreenQuad = new PrimitiveComponent("ScreenQuad");
		ScreenQuad->SetStaticMesh(&BaseShapes::Plane, 1);

		PointLightSphere = new PrimitiveComponent("PointLightSphere");
		PointLightSphere->SetStaticMesh(Sphere, 0);

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

		SkyCubemap_Top = new Image(Path::TextureRelativePath("SkyCube/T_SkyCubemap_Top.jpg").c_str());
		SkyCubemap_Bottom = new Image(Path::TextureRelativePath("SkyCube/T_SkyCubemap_Bottom.jpg").c_str());
		SkyCubemap_Right = new Image(Path::TextureRelativePath("SkyCube/T_SkyCubemap_Right.jpg").c_str());
		SkyCubemap_Left = new Image(Path::TextureRelativePath("SkyCube/T_SkyCubemap_Left.jpg").c_str());
		SkyCubemap_Front = new Image(Path::TextureRelativePath("SkyCube/T_SkyCubemap_Front.jpg").c_str());
		SkyCubemap_Back = new Image(Path::TextureRelativePath("SkyCube/T_SkyCubemap_Back.jpg").c_str());

		DirectionalLightIconImage = new Image(Path::TextureRelativePath("Icons/T_DirectionalLight_Icon_196x196.jpg").c_str());
		SkyLightIconImage = new Image(Path::TextureRelativePath("Icons/T_SkyLight_Icon_176x176.jpg").c_str());
			

		TileTexture = new Texture2D(TileImage);
		WallTexture = new Texture2D(WallImage);
		SkyTexture = new Texture2D(SkyImage);
		RgbTexture = new Texture2D(RgbImage);

		Rock_Al_Texture = new Texture2D(Rock_Al_Image);
		Rock_N_Texture = new Texture2D(Rock_N_Image);
		Rock_S_R_M_AO_Texture = new Texture2D(Rock_S_R_M_AO_Image);

		WoodenFloor_Al_Texture = new Texture2D(WoodenFloor_Al_Image);
		WoodenFloor_N_Texture = new Texture2D(WoodenFloor_N_Image);
		WoodenFloor_S_R_M_AO_Texture = new Texture2D(WoodenFloor_S_R_M_AO_Image);

		SkyCubemapTexture = new TextureCube(SkyCubemap_Top, SkyCubemap_Bottom, SkyCubemap_Right, SkyCubemap_Left,
			SkyCubemap_Front, SkyCubemap_Back);

		DirectionalLightIconTexture = new Texture2D(DirectionalLightIconImage);
		SkyLightIconTexture = new Texture2D(SkyLightIconImage);

		BaseShader = new Shader(Path::ShaderRelativePath("BaseShader.glsl"));
		SkyShader = new Shader(Path::ShaderRelativePath("SkySphere.glsl"));
		GizmoShader = new Shader(Path::ShaderRelativePath("Gizmo.glsl"));
		PostProcessShader = new Shader(Path::ShaderRelativePath("PostProcess.glsl"));
		RockShader = new Shader(Path::ShaderRelativePath("RockShader.glsl"));
		ResolvedShader = new Shader(Path::ShaderRelativePath("ResolvedShader.glsl"));
		ShadowmapShader = new Shader(Path::ShaderRelativePath("ShadowMapShader.glsl"));
		PointLightShader = new Shader(Path::ShaderRelativePath("PointLightShader.glsl"));
		ArrowShader = new Shader(Path::ShaderRelativePath("ArrowShader.glsl"));
		BillboardShader = new Shader(Path::ShaderRelativePath("BillboardShader.glsl"));
		BasepassShader = new Shader(Path::ShaderRelativePath("BasePassShader.glsl"));
	}
}
