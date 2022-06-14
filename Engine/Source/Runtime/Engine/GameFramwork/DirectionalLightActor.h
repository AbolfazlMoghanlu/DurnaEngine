#pragma once

#include "Runtime/Engine/Actor.h"

namespace Durna
{
	class DirectionalLightComponent;
	class PrimitiveComponent;
	class BillboardComponent;

	class DirectionalLightActor : public Actor
	{
	public:
		DirectionalLightActor();
		virtual ~DirectionalLightActor();

		DirectionalLightComponent* GetLightComponent() const;

	protected:
		std::unique_ptr<DirectionalLightComponent> LightSourceComponent;

#if WITH_EDITOR
		std::unique_ptr<PrimitiveComponent> ArrowComponent;
		std::unique_ptr<BillboardComponent> Billboard;
#endif
	private:
		
	};
}