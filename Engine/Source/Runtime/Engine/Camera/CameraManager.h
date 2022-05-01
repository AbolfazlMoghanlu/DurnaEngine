#pragma once

#include "Runtime\Engine\Camera\Camera.h"
#include "Runtime/Math/Vector3.h"
#include "Runtime/Math/Rotator.h"
#include "Runtime/Math/Matrix.h"

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

		static float* GetProjectionMatrix();
		static void UpdateProjectionMatrix();
		static float GetWFactor();

		static bool IsDirtyProjection();
		static void MarkDirtyProjection();

	private:
		static Camera* ActiveCamera;
		static bool bDirtyProjection;

		static Matrix<float> ProjectionMatrix;
	};
}

