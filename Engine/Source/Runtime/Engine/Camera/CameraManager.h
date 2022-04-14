#pragma once

#include "Runtime\Engine\Camera\Camera.h"
#include "Runtime/Math/Vector3.h"

namespace Durna
{
	class CameraManager
	{
	public:
		static Vector3f GetCameraPosition();

		static Camera* GetActiveCamera();

		static void SetActiveCamera(Camera* InCamera);

		static void AddActiveCameraWorldOffset(const Vector3f& Offset);

		static float CameraSpeed;

	private:
		static Camera* ActiveCamera;
	};
}

