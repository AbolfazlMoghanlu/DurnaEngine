#pragma once

#include "Runtime/Engine/Actor.h"

namespace Durna
{
	class CameraComponent;

	class CameraActor : public Actor
	{
	public:
		CameraActor();
		virtual ~CameraActor();

		CameraComponent* GetCameraComponent() const;

#if WITH_EDITOR 
		virtual bool IsVisibleInWorldOutliner() const override {return false;}
#endif

	private:
		std::unique_ptr<CameraComponent> CameraComp;
	};
}

