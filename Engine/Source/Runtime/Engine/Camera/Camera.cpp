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

}