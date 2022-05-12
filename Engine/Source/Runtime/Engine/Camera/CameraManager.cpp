#include "DurnaPCH.h"
#include "CameraManager.h"
#include "Runtime/Engine/Camera/CameraComponent.h"

#include "Runtime/Math/PrespectiveMatrix.h"
#include "Runtime/Math/OrthoMatrix.h"

namespace Durna
{
	CameraManager* CameraManager::SingltonInstance;

	CameraManager* CameraManager::Get()
	{
		if (!SingltonInstance)
		{
			SingltonInstance = new CameraManager;
		}

		return SingltonInstance;
	}

	void CameraManager::Tick(float DeltaTime)
	{
		GetView(CachedLocation, CachedRotation);
		UpdateCameraVectors();
	}

	void CameraManager::UpdateCameraVectors()
	{
		ForwardVector = CachedRotation.GetForwardVector();
		RightVector = Vector3f::CrossProduct(Vector3f::UpVector, ForwardVector).Normalize();
		UpVector = Vector3f::CrossProduct(ForwardVector, RightVector).Normalize();
	}

	void CameraManager::GetView(Vector3f& ViewLocation, Rotatorf& ViewRotation)
	{
		if (ActiveCamera)
		{
			LimitViewPitch();

			ViewLocation = ActiveCamera->GetWorldLocation();
			ViewRotation = ActiveCamera->GetWorldRotation();
		}
	}

	CameraComponent* CameraManager::GetActiveCamera()
	{
		return ActiveCamera;
	}

	void CameraManager::SetActiveCamera(CameraComponent* InCamera)
	{
		ActiveCamera = InCamera;
		MarkDirtyProjection();
	}

	Vector3f CameraManager::GetViewLocation() const
	{
		return CachedLocation;
	}

	Rotatorf CameraManager::GetViewRotation() const
	{
		return CachedRotation;
	}

	float CameraManager::GetMinPitch()
	{
		return MinPitch;
	}

	void CameraManager::SetMinPitch(float InMinPitch)
	{
		MinPitch = InMinPitch;
	}

	float CameraManager::GetMaxPitch()
	{
		return MaxPitch;
	}

	void CameraManager::SetMaxPitch(float InMaxPitch)
	{
		MaxPitch = MinPitch;
	}

	float* CameraManager::GetProjectionMatrix()
	{
		if (IsDirtyProjection())
		{
			UpdateProjectionMatrix();
			bDirtyProjection = false;
		}
		return ProjectionMatrix.M[0];
	}

	void CameraManager::UpdateProjectionMatrix()
	{
		if (ActiveCamera)
		{
			if (ActiveCamera->GetProjectionMode() == EProjectionMode::Perspective)
			{
				ProjectionMatrix = PrespectiveMatrix(ActiveCamera->GetFOV(), ActiveCamera->GetPerspectiveWidth(),
					ActiveCamera->GetPerspectiveHeight(), ActiveCamera->GetPerspectiveMinZ(), ActiveCamera->GetPerspectiveMaxZ());
			}

			else if (ActiveCamera->GetProjectionMode() == EProjectionMode::Orthographic)
			{
				ProjectionMatrix = OrthoMatrix(ActiveCamera->GetOrthographicWidth(), ActiveCamera->GetOrthographicHeight(),
					ActiveCamera->GetOrthographicZScale(), ActiveCamera->GetOrthographicZOffset());
			}
		}
	}

	float CameraManager::GetWFactor()
	{
		if (ActiveCamera)
		{
			return ActiveCamera->GetProjectionMode() == EProjectionMode::Perspective ?
				ActiveCamera->GetPerspectiveMaxZ() - ActiveCamera->GetPerspectiveMinZ() : 
				ActiveCamera->GetOrthographicZScale();
		}

		return 1.0f;
	}

	bool CameraManager::IsDirtyProjection()
	{
		return bDirtyProjection;
	}

	void CameraManager::MarkDirtyProjection()
	{
		bDirtyProjection = true;
	}

	void CameraManager::LimitViewPitch()
	{
		Rotatorf CameraRotation = ActiveCamera->GetWorldRotation();
		float ClampedPitch = Math::Clamp<float>(CameraRotation.Pitch, MinPitch, MaxPitch);
		ActiveCamera->SetRelativeRotation(Rotatorf(ClampedPitch, CameraRotation.Yaw, CameraRotation.Roll));
	}

	float* CameraManager::GetCameraViewMatrix()
	{
		UpdateViewMatrix();
		return ViewMatrix.M[0];
	}

	void CameraManager::UpdateViewMatrix()
	{
		Vector3f CameraPostition = CachedLocation;

		const Vector3f& ZAxis = ForwardVector;
		const Vector3f& XAxis = RightVector;
		const Vector3f& YAxis = UpVector;

		for (int32 RowIndex = 0; RowIndex < 3; RowIndex++)
		{
			ViewMatrix.M[RowIndex][0] = RowIndex == 0 ? XAxis.X : RowIndex == 1 ? XAxis.Y : XAxis.Z;
			ViewMatrix.M[RowIndex][1] = RowIndex == 0 ? YAxis.X : RowIndex == 1 ? YAxis.Y : YAxis.Z;
			ViewMatrix.M[RowIndex][2] = RowIndex == 0 ? ZAxis.X : RowIndex == 1 ? ZAxis.Y : ZAxis.Z;
			ViewMatrix.M[RowIndex][3] = 0.0f;
		}

		ViewMatrix.M[3][0] = Vector3f::DotProduct(CameraPostition * -1, XAxis);
		ViewMatrix.M[3][1] = Vector3f::DotProduct(CameraPostition * -1, YAxis);
		ViewMatrix.M[3][2] = Vector3f::DotProduct(CameraPostition * -1, ZAxis);
		ViewMatrix.M[3][3] = 1.0f;
	}
}
