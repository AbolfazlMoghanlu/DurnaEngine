#pragma once

#include "Runtime/Engine/Actor.h"

namespace Durna
{
	class SkyLightComponent;
	class BillboardComponent;

	class SkyLightActor : public Actor
	{
	public:
		SkyLightActor();
		virtual ~SkyLightActor();

		SkyLightComponent* GetLightComponent() const;

	protected:
		std::unique_ptr<SkyLightComponent> LightSource;

#if WITH_EDITOR
		std::unique_ptr<BillboardComponent> Billboard;
#endif

	private:

	};
}

