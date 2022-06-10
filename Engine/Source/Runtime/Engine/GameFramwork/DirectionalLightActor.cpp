#include "DurnaPCH.h"
#include "DirectionalLightActor.h"
#include "Runtime/Components/DirectionalLightComponent.h"

namespace Durna
{
	DirectionalLightActor::DirectionalLightActor()
	{
		LightSourceComponent = std::make_unique<DirectionalLightComponent>("Light Source");
		AttachSceneComponent(LightSourceComponent.get());
	}

	DirectionalLightActor::~DirectionalLightActor()
	{

	}

	DirectionalLightComponent* DirectionalLightActor::GetLightComponent() const
	{
		return LightSourceComponent.get();
	}
}