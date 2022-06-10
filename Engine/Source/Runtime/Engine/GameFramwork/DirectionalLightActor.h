#pragma once

#include "Runtime/Engine/Actor.h"

namespace Durna
{
	class DirectionalLightComponent;
	class PrimitiveComponent;

	class DirectionalLightActor : public Actor
	{
	public:
		DirectionalLightActor();
		virtual ~DirectionalLightActor();

		DirectionalLightComponent* GetLightComponent() const;

	protected:
		std::unique_ptr<DirectionalLightComponent> LightSourceComponent;
		std::unique_ptr<PrimitiveComponent> ArrowComponent;
		
	private:
		
	};
}