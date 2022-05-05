#include "DurnaPCH.h"
#include "AssetLibrary.h"

#include "Runtime/Engine/StaticMesh.h"
#include "Runtime/Misc/ModelLoader.h"
#include "Runtime/Engine/Image/Image.h"
#include "Runtime/Renderer/Texture.h"
#include "Runtime/Renderer/Shader.h"
#include "Runtime/Renderer/Material.h"

namespace Durna
{
	StaticMesh* AssetLibrary::GizmoMesh;

	Image* AssetLibrary::TileImage;
	Image* AssetLibrary::WallImage;
	Image* AssetLibrary::SkyImage;
	Image* AssetLibrary::RgbImage;

	Texture* AssetLibrary::TileTexture;
	Texture* AssetLibrary::WallTexture;
	Texture* AssetLibrary::SkyTexture;

	Texture* AssetLibrary::RgbTexture;

	Shader* AssetLibrary::BaseShader;
	Shader* AssetLibrary::SkyShader;
	Shader* AssetLibrary::GizmoShader;

	Material* AssetLibrary::BaseMaterial;
	Material* AssetLibrary::SkyMaterial;
	Material* AssetLibrary::GizmoMaterial;

	void AssetLibrary::Init()
	{
		GizmoMesh = new StaticMesh;
		ModelLoader::Load(Path::ModelRelativePath("Gizmo.obj"), GizmoMesh);

		TileImage = new Image(Path::TextureRelativePath("T_TiledTexureCoordiante.png").c_str());
		WallImage = new Image(Path::TextureRelativePath("T_Wall.jpg").c_str());
		SkyImage = new Image(Path::TextureRelativePath("T_Sky.jpg").c_str());
		RgbImage = new Image(Path::TextureRelativePath("T_Rgb.png").c_str());

		TileTexture = new Texture(TileImage);
		WallTexture = new Texture(WallImage);
		SkyTexture = new Texture(SkyImage);
		RgbTexture = new Texture(RgbImage);

		BaseShader = new Shader(Path::ShaderRelativePath("BaseShader.glsl"));
		SkyShader = new Shader(Path::ShaderRelativePath("SkySphere.glsl"));
		GizmoShader = new Shader(Path::ShaderRelativePath("Gizmo.glsl"));

		BaseMaterial = new Material(BaseShader, 2);
		BaseMaterial->AddTextureElement(TextureElement("texture1", TileTexture));
		BaseMaterial->AddTextureElement(TextureElement("texture2", WallTexture));

		SkyMaterial = new Material(SkyShader, 1);
		SkyMaterial->AddTextureElement(TextureElement("SkyTexture", SkyTexture));

		GizmoMaterial = new Material(GizmoShader, 1);
		GizmoMaterial->AddTextureElement(TextureElement("BaseColor", RgbTexture));
	}
}
