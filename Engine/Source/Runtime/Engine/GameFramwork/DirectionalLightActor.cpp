#include "DurnaPCH.h"
#include "DirectionalLightActor.h"
#include "Runtime/Components/DirectionalLightComponent.h"
#include "Runtime/Components/PrimitiveComponent.h"
#include "Runtime/Components/BillboardComponent.h"
#include "Runtime/Asset/AssetLibrary.h"
#include "Runtime/Renderer/Material.h"
#include "Runtime/Renderer/Texture2D.h"

namespace Durna
{
	DirectionalLightActor::DirectionalLightActor()
	{
		LightSourceComponent = std::make_unique<DirectionalLightComponent>("Light Source");
		AttachSceneComponent(LightSourceComponent.get());

#if WITH_EDITOR

		Billboard = std::make_unique<BillboardComponent>("Billboard");
		AttachSceneComponent(Billboard.get());
		Billboard->SetTexture(AssetLibrary::DirectionalLightIconTexture);
		Billboard->SetRelativeScale(Vector3f(0.1f));

		ArrowComponent = std::make_unique<PrimitiveComponent>("Arrow");
		AttachSceneComponent(ArrowComponent.get(), Billboard.get());
		
		ArrowComponent->SetStaticMesh(AssetLibrary::ArrowMesh);
		ArrowComponent->GetMaterial()->SetShader(AssetLibrary::ArrowShader);
		ArrowComponent->GetMaterial()->SetShadingModel(EShadingModel::Unlit);
		ArrowComponent->SetRelativeScale(Vector3f(1.0f));
		ArrowComponent->SetRelativeLocation(Vector3f(0.0f, 0.0f, -0.1f));
		ArrowComponent->SetCastShadow(false);

#endif
	}

	DirectionalLightActor::~DirectionalLightActor()
	{

	}

	DirectionalLightComponent* DirectionalLightActor::GetLightComponent() const
	{
		return LightSourceComponent.get();
	}
}