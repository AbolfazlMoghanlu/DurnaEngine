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

	Texture* AssetLibrary::TileTexture;
	Texture* AssetLibrary::WallTexture;
	
	Shader* AssetLibrary::BaseShader;
	
	Material* AssetLibrary::BaseMaterial;

	void AssetLibrary::Init()
	{
		TileImage = new Image(Path::TextureRelativePath("T_TiledTexureCoordiante.png").c_str());
		WallImage = new Image(Path::TextureRelativePath("T_Wall.jpg").c_str());

		TileTexture = new Texture(TileImage);
		WallTexture = new Texture(WallImage);

		BaseShader = new Shader(Path::ShaderRelativePath("BaseShader.glsl"));

		BaseMaterial = new Material(BaseShader, 2);
		BaseMaterial->AddTextureElement(TextureElement("texture1", TileTexture));
		BaseMaterial->AddTextureElement(TextureElement("texture2", WallTexture));
	}
}
