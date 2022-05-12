#include "DurnaPCH.h"
#include "CameraActor.h"

#include "Runtime/Engine/Camera/CameraComponent.h"

namespace Durna
{
	CameraActor::CameraActor() : Actor()
	{
		CameraComp = std::unique_ptr<CameraComponent>(new CameraComponent);
		AttachSceneComponent(CameraComp.get());	
	}

	CameraActor::~CameraActor()
	{

	}

	CameraComponent* CameraActor::GetCameraComponent() const
	{
		return CameraComp.get();
	}
}