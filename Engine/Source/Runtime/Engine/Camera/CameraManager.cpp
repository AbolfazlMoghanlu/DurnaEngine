#include "DurnaPCH.h"
#include "CameraManager.h"

namespace Durna
{
	Camera* CameraManager::ActiveCamera;

	float CameraManager::CameraMoveSpeed = 0.01f;
	float CameraManager::CameraRotationSpeed = 3.0f;

	Vector3f CameraManager::GetActiveCameraPosition()
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

	void CameraManager::GetCameraViewMatrix(float* A)
	{
		Vector3f CameraDirection = GetActiveCameraRotation().GetForwardVector();
		Vector3f CameraRightVector = GetActiveCameraRotation().GetRightVector();
		Vector3f CameraUpVector = GetActiveCameraRotation().GetUpVector();

		float* M = new float[16];
		A[0] = CameraRightVector.X;
		A[1] = CameraRightVector.Y;
		A[2] = CameraRightVector.Z;
		A[3] = 0;
		A[4] = CameraUpVector.X;
		A[5] = CameraUpVector.Y;
		A[6] = CameraUpVector.Z;
		A[7] = 0;
		A[8] = CameraDirection.X;
		A[9] = CameraDirection.Y;
		A[10] = CameraDirection.Z;
		A[11] = 0;
		A[12] = 0;
		A[13] = 0;
		A[14] = 0;
		A[15] = 1;
	}

}
