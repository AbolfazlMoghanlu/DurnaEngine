#include "DurnaPCH.h"
#include "DirectionalLightActor.h"
#include "Runtime/Components/DirectionalLightComponent.h"
#include "Runtime/Components/PrimitiveComponent.h"
#include "Runtime/Assets/AssetLibrary.h"
#include "Runtime/Renderer/Material.h"

namespace Durna
{
	DirectionalLightActor::DirectionalLightActor()
	{
		LightSourceComponent = std::make_unique<DirectionalLightComponent>("Light Source");
		AttachSceneComponent(LightSourceComponent.get());

		ArrowComponent = std::make_unique<PrimitiveComponent>("Arrow");
		AttachSceneComponent(ArrowComponent.get(), LightSourceComponent.get());

		ArrowComponent->SetStaticMesh(AssetLibrary::ArrowMesh);
		ArrowComponent->GetMaterial()->SetShader(AssetLibrary::ArrowShader);
		ArrowComponent->SetRelativeScale(Vector3f(0.25f));
		ArrowComponent->SetCastShadow(false);
	}

	DirectionalLightActor::~DirectionalLightActor()
	{

	}

	DirectionalLightComponent* DirectionalLightActor::GetLightComponent() const
	{
		return LightSourceComponent.get();
	}
}