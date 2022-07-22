#include "DurnaPCH.h"
#include "SkySphereComponent.h"

#include "Runtime/Asset/AssetLibrary.h"
#include "Runtime/Renderer/Material.h"
#include "Runtime/Renderer/Shader.h"
#include "Runtime/Renderer/Texture.h"
#include "Runtime/Renderer/TextureCube.h"

#if WITH_EDITOR
#include "Editor/DetailsPanel/SkySphereComponentPanel.h"
#endif

namespace Durna
{
	SkySphereComponent::SkySphereComponent(const std::string& InLabel) : PrimitiveComponent(InLabel)
	{
		SetStaticMesh(AssetLibrary::FlipedSphere, 0);
		GetMaterial()->SetShader(AssetLibrary::SkyShader);
		//GetMaterial()->AddTextureElement(TextureElement("SkyCubemap", AssetLibrary::SkyCubemapTexture));
		SetCubemap(AssetLibrary::SkyCubemapTexture);

		BindPreDraw(
			[](PrimitiveComponent* InComponent, Shader* InShader)
			{
				InShader->SetUniformVec3f("OverallColor", static_cast<SkySphereComponent*>(InComponent)->OverallColor);
			});

		SetCastShadow(false);
		GetMaterial()->SetShadingModel(EShadingModel::Unlit);
		SetRelativeScale(Vector3f(500.0f));

#if WITH_EDITOR
		Panel = new SkySphereComponentPanel(this);
#endif
	}

	SkySphereComponent::~SkySphereComponent()
	{
#if WITH_EDITOR
		delete Panel;
#endif
	}

	LinearColor SkySphereComponent::GetOverallColor() const
	{
		return OverallColor;
	}

	void SkySphereComponent::SetOverallColor(const LinearColor& InOverallColor)
	{
		OverallColor = InOverallColor;
	}

	Texture* SkySphereComponent::GetCubemap() const
	{
		return Cubemap;
	}

	void SkySphereComponent::SetCubemap(Texture* InTexture)
	{
		GetMaterial()->ResetTextureElements();
		GetMaterial()->AddTextureElement(TextureElement("SkyCubemap", InTexture));
		Cubemap = InTexture;
	}

}