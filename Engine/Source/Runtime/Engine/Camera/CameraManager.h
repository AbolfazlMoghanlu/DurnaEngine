#pragma once

#include "Runtime\Engine\Camera\Camera.h"
#include "Runtime/Math/Vector3.h"
#include "Runtime/Math/Rotator.h"

namespace Durna
{
	class CameraManager
	{
	public:
		static Camera* GetActiveCamera();
		static void SetActiveCamera(Camera* InCamera);

		static Vector3f GetActiveCameraPosition();
		static void AddActiveCameraWorldOffset(const Vector3f& Offset);

		static Rotatorf GetActiveCameraRotation();
		static void AddActiveCameraWorldRotation(const Rotatorf& InRotator);

		static void GetCameraViewMatrix(float* A);

		static float CameraMoveSpeed;
		static float CameraRotationSpeed;

	private:
		static Camera* ActiveCamera;
	};
}

