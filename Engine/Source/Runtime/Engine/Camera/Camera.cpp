#include "DurnaPCH.h"
#include "Camera.h"

namespace Durna
{

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
}