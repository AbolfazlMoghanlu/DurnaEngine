#include "DurnaPCH.h"
#include "DirectionalLightActor.h"
#include "Runtime/Components/DirectionalLightComponent.h"
#include "Runtime/Components/PrimitiveComponent.h"
#include "Runtime/Components/BillboardComponent.h"
#include "Runtime/Assets/AssetLibrary.h"
#include "Runtime/Renderer/Material.h"


namespace Durna
{
	DirectionalLightActor::DirectionalLightActor()
	{
		LightSourceComponent = std::make_unique<DirectionalLightComponent>("Light Source");
		AttachSceneComponent(LightSourceComponent.get());

#if WITH_EDITOR
		ArrowComponent = std::make_unique<PrimitiveComponent>("Arrow");
		AttachSceneComponent(ArrowComponent.get(), LightSourceComponent.get());

		ArrowComponent->SetStaticMesh(AssetLibrary::ArrowMesh);
		ArrowComponent->GetMaterial()->SetShader(AssetLibrary::ArrowShader);
		ArrowComponent->GetMaterial()->SetShadingModel(EShadingModel::Unlit);
		ArrowComponent->SetRelativeScale(Vector3f(0.25f));
		ArrowComponent->SetCastShadow(false);

		Billboard = std::make_unique<BillboardComponent>("Billboard");
		AttachSceneComponent(Billboard.get());
		Billboard->SetTexture(AssetLibrary::DirectionalLightTexture);
		Billboard->SetRelativeScale(Vector3f(0.1f));
		Billboard->SetRelativeLocation(Vector3f(0.0f, 0.0f, 0.1f));
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