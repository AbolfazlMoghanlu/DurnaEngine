#include "DurnaPCH.h"
#include "CameraManager.h"

#include "Runtime/Math/PrespectiveMatrix.h"
#include "Runtime/Math/OrthoMatrix.h"

namespace Durna
{
	Camera* CameraManager::ActiveCamera = nullptr;

	Vector3f CameraManager::ForwardVector(1.0f, 0.0f, 0.0f);
	Vector3f CameraManager::RightVector(0.0f, 1.0f, 0.0f);
	Vector3f CameraManager::UpVector(0.0f, 0.0f, 1.0f);

	Matrix<float> CameraManager::ProjectionMatrix;
	bool CameraManager::bDirtyProjection = true;

	Matrix<float> CameraManager::ViewMatrix;
	bool CameraManager::bDirtyView = true;

	float CameraManager::CameraMoveSpeed = 2.0f;
	float CameraManager::CameraRotationSpeed = 0.1f;


	void CameraManager::Tick(float DeltaTime)
	{
		UpdateCameraVectors();
	}

	void CameraManager::UpdateCameraVectors()
	{
		ForwardVector = GetActiveCameraRotation().GetForwardVector();
		RightVector = Vector3f::CrossProduct(Vector3f::UpVector, ForwardVector).Normalize();
		UpVector = Vector3f::CrossProduct(ForwardVector, RightVector).Normalize();
	}



	Camera* CameraManager::GetActiveCamera()
	{
		return ActiveCamera;
	}

	void CameraManager::SetActiveCamera(Camera* InCamera)
	{
		ActiveCamera = InCamera;
		MarkDirtyProjection();
		MarkDirtyView();
	}

	Vector3f CameraManager::GetActiveCameraLocation()
	{
		return ActiveCamera ? ActiveCamera->GetCameraLocation() : Vector3f(0);
	}

	void CameraManager::AddActiveCameraWorldOffset(const Vector3f& Offset)
	{
		ActiveCamera->AddCameraWorldOffset(Offset * CameraMoveSpeed);
	}

	void CameraManager::SetActiveCameraLocation(const Vector3f& InLocation)
	{
		ActiveCamera->SetCameraWorldLocation(InLocation);
	}

	void CameraManager::MoveForward(float Delta)
	{
		SetActiveCameraLocation(GetActiveCameraLocation() + ForwardVector * Delta * CameraMoveSpeed);
	}

	void CameraManager::MoveRight(float Delta)
	{
		SetActiveCameraLocation(GetActiveCameraLocation() + RightVector * Delta * CameraMoveSpeed);
	}

	Rotatorf CameraManager::GetActiveCameraRotation()
	{
		return ActiveCamera ? ActiveCamera->GetCameraRotation() : Rotatorf::ZeroRotator;
	}

	void CameraManager::AddActiveCameraWorldRotation(const Rotatorf& InRotator)
	{
		ActiveCamera->AddCameraWorldRotation(InRotator * CameraRotationSpeed);
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

	bool CameraManager::IsDirtyView()
	{
		return bDirtyView;
	}

	void CameraManager::MarkDirtyView()
	{
		bDirtyView = true;
	}

	float* CameraManager::GetCameraViewMatrix()
	{
		if (IsDirtyView())
		{
			UpdateViewMatrix();
			bDirtyView = false;
		}
		return ViewMatrix.M[0];
	}

	void CameraManager::UpdateViewMatrix()
	{
		Vector3f CameraPostition = GetActiveCameraLocation();

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
