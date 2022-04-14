#pragma once

#include "Runtime/Math/Vector3.h"

namespace Durna
{
	class Camera
	{
	public:
		Vector3f GetCameraPosition() const;

		void AddCameraWorldOffset(const Vector3f& PositionOffset);

	private:
		Vector3f Position;


	};
}

