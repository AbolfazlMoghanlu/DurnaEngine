#include "DurnaPCH.h"
#include "Camera.h"
#include "CameraManager.h"

#include "Runtime/Math/Math.h"

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
		CameraManager::MarkDirtyView();
	}

	Rotatorf Camera::GetCameraRotation() const
	{
		return Rotation;
	}

	void Camera::AddCameraWorldRotation(const Rotatorf& RotationOffset)
	{
		Rotatorf CombinedRotation = Rotation + RotationOffset;
		float ClampedPitch = Math::Clamp<float>(CombinedRotation.Pitch, MinPitch, MaxPitch);
		CombinedRotation.Pitch = ClampedPitch;

		Rotation = CombinedRotation;
		CameraManager::MarkDirtyView();
	}


	void Camera::SetProjectionMode(EProjectionMode InProjectionMode)
	{
		ProjectionMode = InProjectionMode;
		CameraManager::MarkDirtyProjection();
		CameraManager::MarkDirtyView();
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

	void Camera::SetOrthographicWidth(float InWidth)
	{
		OrthographicData.Width = InWidth;
		CameraManager::MarkDirtyProjection();
	}

	float Camera::GetOrthographicWidth() const
	{
		return OrthographicData.Width;
	}

	void Camera::SetOrthographicHeight(float InHeight)
	{
		OrthographicData.Heigth = InHeight;
		CameraManager::MarkDirtyProjection();
	}

	float Camera::GetOrthographicHeight() const
	{
		return OrthographicData.Heigth;
	}

	void Camera::SetOrthographicZScale(float InZScale)
	{
		OrthographicData.ZScale = InZScale;
		CameraManager::MarkDirtyProjection();
	}

	float Camera::GetOrthographicZScale() const
	{
		return OrthographicData.ZScale;
	}

	void Camera::SetOrthographicZOffset(float InZOffset)
	{
		OrthographicData.ZOffset = InZOffset;
		CameraManager::MarkDirtyProjection();
	}

	float Camera::GetOrthographicZOffset() const
	{
		return OrthographicData.ZOffset;
	}

}