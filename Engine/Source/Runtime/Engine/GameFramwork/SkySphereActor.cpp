#include "DurnaPCH.h"
#include "SkySphereActor.h"

#include "Runtime/Components/SkySphereComponent.h"

namespace Durna
{
	SkySphereActor::SkySphereActor()
	{
		SkyComponent = std::make_unique<SkySphereComponent>("SkyComponent");
		AttachSceneComponent(SkyComponent.get());


	}

	SkySphereActor::~SkySphereActor()
	{

	}

	SkySphereComponent* SkySphereActor::GetSkyComponent() const
	{
		return SkyComponent.get();
	}
}