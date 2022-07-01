#pragma once

#include "Runtime/Engine/Actor.h"

namespace Durna
{
	class SkySphereComponent;

	class SkySphereActor : public Actor
	{
	public:
		SkySphereActor();
		virtual ~SkySphereActor();

		SkySphereComponent* GetSkyComponent() const;

	protected:
		std::unique_ptr<SkySphereComponent> SkyComponent;
	};
}