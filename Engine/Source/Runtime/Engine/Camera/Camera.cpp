#include "DurnaPCH.h"
#include "Camera.h"
#include "CameraManager.h"

namespace Durna
{
	Camera::Camera()
	{

	}

	Vector3f Camera::GetCameraPosition() const
	{
		return Position;
	}

	void Camera::AddCameraWorldOffset(const Vector3f& PositionOffset)
	{
		Position += PositionOffset;
	}

	Rotatorf Camera::GetCameraRotation() const
	{
		return Rotation;
	}

	void Camera::AddCameraWorldRotation(const Rotatorf& RotationOffset)
	{
		Rotation = Rotatorf::CombineRotators(Rotation, RotationOffset);
	}


	void Camera::SetProjectionMode(EProjectionMode InProjectionMode)
	{
		ProjectionMode = InProjectionMode;
		CameraManager::MarkDirtyProjection();
	}

	EProjectionMode Camera::GetProjectionMode() const
	{
		return ProjectionMode;
	}

	void Camera::SetFOV(float InFOV)
	{
		PerspectiveData.FOV = InFOV;
		CameraManager::MarkDirtyProjection();
	}

	float Camera::GetFOV() const
	{
		return PerspectiveData.FOV;
	}

	void Camera::SetPerspectiveWidth(float InWidth)
	{
		PerspectiveData.Width = InWidth;
		CameraManager::MarkDirtyProjection();
	}

	float Camera::GetPerspectiveWidth() const
	{
		return PerspectiveData.Width;
	}

	void Camera::SetPerspectiveHeight(float InHeight)
	{
		PerspectiveData.Heigth = InHeight;
		CameraManager::MarkDirtyProjection();
	}

	float Camera::GetPerspectiveHeight() const
	{
		return PerspectiveData.Heigth;
	}

	void Camera::SetPerspectiveMinZ(float InMinZ)
	{
		PerspectiveData.MinZ = InMinZ;
		CameraManager::MarkDirtyProjection();
	}

	float Camera::GetPerspectiveMinZ() const
	{
		return PerspectiveData.MinZ;
	}

	void Camera::SetPerspectiveMaxZ(float InMaxZ)
	{
		PerspectiveData.MaxZ = InMaxZ;
		CameraManager::MarkDirtyProjection();
	}

	float Camera::GetPerspectiveMaxZ() const
	{
		return PerspectiveData.MaxZ;
	}

}