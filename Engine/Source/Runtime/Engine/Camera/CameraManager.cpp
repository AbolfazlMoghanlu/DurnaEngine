#include "DurnaPCH.h"
#include "CameraManager.h"

#include "Runtime/Math/PrespectiveMatrix.h"
#include "Runtime/Math/OrthoMatrix.h"

namespace Durna
{
	Camera* CameraManager::ActiveCamera = nullptr;
	bool CameraManager::bDirtyProjection = true;

	bool CameraManager::bDirtyView = true;

	Matrix<float> CameraManager::ProjectionMatrix;
	Matrix<float> CameraManager::ViewMatrix;

	float CameraManager::CameraMoveSpeed = 0.01f;
	float CameraManager::CameraRotationSpeed = 3.0f;

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
		MarkDirtyProjection();
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
		Vector3f CameraPostition = GetActiveCameraPosition();

		Vector3f CameraDirection = GetActiveCameraRotation().GetForwardVector();
		Vector3f CameraRightVector = GetActiveCameraRotation().GetRightVector();
		Vector3f CameraUpVector = GetActiveCameraRotation().GetUpVector();

		const Vector3f ZAxis = GetActiveCameraRotation().GetForwardVector();
		const Vector3f XAxis = GetActiveCameraRotation().GetRightVector();
		const Vector3f YAxis = GetActiveCameraRotation().GetUpVector();

		for (int32 RowIndex = 0; RowIndex < 3; RowIndex++)
		{
			if (RowIndex == 0)
			{
				ViewMatrix.M[RowIndex][0] = XAxis.X;
				ViewMatrix.M[RowIndex][1] = YAxis.X;
				ViewMatrix.M[RowIndex][2] = ZAxis.X;
				ViewMatrix.M[RowIndex][3] = 0.0f;
			}
			else if (RowIndex == 1)
			{
				ViewMatrix.M[RowIndex][0] = XAxis.Y;
				ViewMatrix.M[RowIndex][1] = YAxis.Y;
				ViewMatrix.M[RowIndex][2] = ZAxis.Y;
				ViewMatrix.M[RowIndex][3] = 0.0f;
			}
			else if (RowIndex == 2)
			{
				ViewMatrix.M[RowIndex][0] = XAxis.Z;
				ViewMatrix.M[RowIndex][1] = YAxis.Z;
				ViewMatrix.M[RowIndex][2] = ZAxis.Z;
				ViewMatrix.M[RowIndex][3] = 0.0f;
			}
		}

		ViewMatrix.M[3][0] = Vector3f::DotProduct(CameraPostition * -1, XAxis);
		ViewMatrix.M[3][1] = Vector3f::DotProduct(CameraPostition * -1, YAxis);
		ViewMatrix.M[3][2] = Vector3f::DotProduct(CameraPostition * -1, ZAxis);
		ViewMatrix.M[3][3] = 1.0f;

		/*
		ViewMatrix.M[0] = CameraRightVector.X;
		ViewMatrix.M[1] = CameraRightVector.Y;
		ViewMatrix.M[2] = CameraRightVector.Z;
		ViewMatrix.M[3] = 0;
		ViewMatrix.M[4] = CameraUpVector.X;
		ViewMatrix.M[5] = CameraUpVector.Y;
		ViewMatrix.M[6] = CameraUpVector.Z;
		ViewMatrix.M[7] = 0;
		ViewMatrix.M[8] = CameraDirection.X;
		ViewMatrix.M[9] = CameraDirection.Y;
		ViewMatrix.M[10] = CameraDirection.Z;
		ViewMatrix.M[11] = 0;
		ViewMatrix.M[12] = 0;
		ViewMatrix.M[13] = 0;
		ViewMatrix.M[14] = 0;
		ViewMatrix.M[15] = 1;
		*/
	}

}
