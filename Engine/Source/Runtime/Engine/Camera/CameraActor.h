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

	private:
		std::unique_ptr<CameraComponent> CameraComp;
	};
}

