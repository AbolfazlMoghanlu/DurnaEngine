#pragma once

#include "Runtime/Math/Vector3.h"
#include "Runtime/Math/Rotator.h"
#include "Runtime/Math/Matrix.h"

namespace Durna
{
	class CameraComponent;

	class CameraManager
	{
	public:
		static CameraManager* Get();

		void Tick(float DeltaTime);
		void UpdateCameraVectors();

		CameraComponent* GetActiveCamera();
		void SetActiveCamera(CameraComponent* InCamera);

		Vector3f GetViewLocation() const;
		Rotatorf GetViewRotation() const;

		// -------------------------- rotation limits ---------------------
		void LimitViewPitch();

		float GetMinPitch();
		void SetMinPitch(float InMinPitch);

		float GetMaxPitch();
		void SetMaxPitch(float InMinPitch);

		// --------------------------- view matrix ------------------------
		float* GetCameraViewMatrix();
		void UpdateViewMatrix();

		// --------------------------- projection matrix ------------------------
		float* GetProjectionMatrix();
		void UpdateProjectionMatrix();
		float GetWFactor();

		bool IsDirtyProjection();
		void MarkDirtyProjection();

	protected:
		virtual void GetView(Vector3f& ViewLocation, Rotatorf& ViewRotation);

	private:
		static CameraManager* SingltonInstance;

		CameraComponent* ActiveCamera;
		bool bDirtyProjection;

		Vector3f ForwardVector;
		Vector3f RightVector;
		Vector3f UpVector;

		Matrix<float> ProjectionMatrix;
		Matrix<float> ViewMatrix;

		Vector3f CachedLocation;
		Rotatorf CachedRotation;

		float MinPitch = -85.0f;
		float MaxPitch = 85.0f;
	};
}