#pragma once

#include "Runtime/Math/Vector3.h"
#include "Runtime/Math/Rotator.h"

namespace Durna
{
	class Camera
	{
	public:
		Vector3f GetCameraPosition() const;
		void AddCameraWorldOffset(const Vector3f& PositionOffset);

		Rotatorf GetCameraRotation() const;
		void AddCameraWorldRotation(const Rotatorf& RotationOffset);

	private:
		Vector3f Position;
		Rotatorf Rotation;
	};
}

