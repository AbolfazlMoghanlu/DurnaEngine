#include "DurnaPCH.h"
#include "CameraManager.h"

namespace Durna
{
	Camera* CameraManager::ActiveCamera;

	float CameraManager::CameraSpeed = 0.01f;

	Vector3f CameraManager::GetCameraPosition()
	{
		return ActiveCamera ? ActiveCamera->GetCameraPosition() : Vector3f(0);
	}

	Camera* CameraManager::GetActiveCamera()
	{
		return ActiveCamera;
	}

	void CameraManager::SetActiveCamera(Camera* InCamera)
	{
		ActiveCamera = InCamera;
	}

	void CameraManager::AddActiveCameraWorldOffset(const Vector3f& Offset)
	{
		ActiveCamera->AddCameraWorldOffset(Offset * CameraSpeed);
	}

	

}
