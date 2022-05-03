#include "DurnaPCH.h"
#include "AssetLibrary.h"

#include "Runtime/Engine/Image/Image.h"
#include "Runtime/Renderer/Texture.h"
#include "Runtime/Renderer/Shader.h"
#include "Runtime/Renderer/Material.h"

namespace Durna
{
	Image* AssetLibrary::TileImage;
	Image* AssetLibrary::WallImage;
	Image* AssetLibrary::SkyImage;

	Texture* AssetLibrary::TileTexture;
	Texture* AssetLibrary::WallTexture;
	Texture* AssetLibrary::SkyTexture;

	Shader* AssetLibrary::BaseShader;
	Shader* AssetLibrary::SkyShader;

	Material* AssetLibrary::BaseMaterial;
	Material* AssetLibrary::SkyMaterial;

	void AssetLibrary::Init()
	{
		TileImage = new Image(Path::TextureRelativePath("T_TiledTexureCoordiante.png").c_str());
		WallImage = new Image(Path::TextureRelativePath("T_Wall.jpg").c_str());
		SkyImage = new Image(Path::TextureRelativePath("T_Sky.jpg").c_str());

		TileTexture = new Texture(TileImage);
		WallTexture = new Texture(WallImage);
		SkyTexture = new Texture(SkyImage);

		BaseShader = new Shader(Path::ShaderRelativePath("BaseShader.glsl"));
		SkyShader = new Shader(Path::ShaderRelativePath("SkySphere.glsl"));

		BaseMaterial = new Material(BaseShader, 2);
		BaseMaterial->AddTextureElement(TextureElement("texture1", TileTexture));
		BaseMaterial->AddTextureElement(TextureElement("texture2", WallTexture));

		SkyMaterial = new Material(SkyShader, 1);
		SkyMaterial->AddTextureElement(TextureElement("SkyTexture", SkyTexture));
	}
}
