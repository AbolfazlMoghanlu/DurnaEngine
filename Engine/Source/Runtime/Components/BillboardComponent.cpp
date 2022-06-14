#include "DurnaPCH.h"
#include "BillboardComponent.h"
#include "Runtime/Renderer/Texture.h"
#include "Runtime/Assets/AssetLibrary.h"
#include "Runtime/Renderer/Material.h"
#include "Runtime/Renderer/Shader.h"
#include "Runtime/Renderer/CommonRenderUniforms.h"

namespace Durna
{
	BillboardComponent::BillboardComponent(const std::string& InLabel)
		: PrimitiveComponent(InLabel)
	{
		SetStaticMesh(AssetLibrary::PlaneMesh, 1);
		GetMaterial()->SetShader(AssetLibrary::BillboardShader);
		GetMaterial()->SetShadingModel(EShadingModel::Unlit);
		SetCastShadow(false);

		BindPreDraw(
			[](PrimitiveComponent* InComponent, Shader* InShader)
			{
				CommonRenderUniforms::UploadOrientation(InShader, InComponent);
				CommonRenderUniforms::UploadCameraLocation(InShader);
				CommonRenderUniforms::UploadRenderTime(InShader);
			});
	}

	BillboardComponent::~BillboardComponent()
	{

	}

	void BillboardComponent::Tick(float DeltaTime)
	{
		PrimitiveComponent::Tick(DeltaTime);


	}

	Texture* BillboardComponent::GetTexture() const
	{
		return SourceTexture;
	}

	void BillboardComponent::SetTexture(Texture* InTexture)
	{
		SourceTexture = InTexture;

		GetMaterial()->ResetTextureElements();

		if (SourceTexture)
		{
			GetMaterial()->AddTextureElement(TextureElement("SpriteTexture", SourceTexture));
		}
	}
}