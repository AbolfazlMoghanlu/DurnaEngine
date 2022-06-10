#pragma once

#include "Runtime/Engine/Actor.h"

namespace Durna
{
	class DirectionalLightComponent;

	class DirectionalLightActor : public Actor
	{
	public:
		DirectionalLightActor();
		virtual ~DirectionalLightActor();

		DirectionalLightComponent* GetLightComponent() const;

	protected:
		std::unique_ptr<DirectionalLightComponent> LightSourceComponent;
		
	private:
		
	};
}