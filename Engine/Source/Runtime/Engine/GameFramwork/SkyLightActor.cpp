#include "DurnaPCH.h"
#include "SkyLightActor.h"

#include "Runtime/Components/SkyLightComponent.h"
#include "Runtime/Components/BillboardComponent.h"
#include "Runtime/Assets/AssetLibrary.h"

namespace Durna
{
	SkyLightActor::SkyLightActor()
	{
		LightSource = std::make_unique<SkyLightComponent>("Light Source");
		AttachSceneComponent(LightSource.get());

#if WITH_EDITOR

		Billboard = std::make_unique<BillboardComponent>("Billboard");
		Billboard->SetTexture(AssetLibrary::SkyLightIconTexture);
		Billboard->SetRelativeScale(Vector3f(0.1f));
		AttachSceneComponent(Billboard.get());

#endif
	}

	SkyLightActor::~SkyLightActor()
	{

	}

	SkyLightComponent* SkyLightActor::GetLightComponent() const
	{
		return LightSource.get();
	}
}