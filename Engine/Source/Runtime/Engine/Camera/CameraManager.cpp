#include "DurnaPCH.h"
#include "CameraManager.h"

namespace Durna
{
	Camera* CameraManager::ActiveCamera;

	float CameraManager::CameraMoveSpeed = 0.01f;
	float CameraManager::CameraRotationSpeed = 1.0f;

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
		ActiveCamera->AddCameraWorldOffset(Offset * CameraMoveSpeed);
	}

	Rotatorf CameraManager::GetActiveCameraRotation()
	{
		return ActiveCamera ? ActiveCamera->GetCameraRotation() : Rotatorf::ZeroRotator;
	}

	void CameraManager::AddActiveCameraWorldRotation(const Rotatorf& InRotator)
	{
		ActiveCamera->AddCameraWorldRotation(InRotator * CameraRotationSpeed);
	}
}
