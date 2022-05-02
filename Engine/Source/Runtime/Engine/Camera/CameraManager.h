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


		static float* GetCameraViewMatrix();
		static void UpdateViewMatrix();

		static bool IsDirtyView();
		static void MarkDirtyView();


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
		static bool bDirtyView;

		static Matrix<float> ProjectionMatrix;
		static Matrix<float> ViewMatrix;
	};
}

