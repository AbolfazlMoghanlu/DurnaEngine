#pragma once

#include "Runtime/Components/SceneComponent.h"
#include "Runtime/Engine/Camera/CameraTypes.h"

namespace Durna
{
	class CameraComponent : public SceneComponent
	{
	public:
		virtual void Tick(float DeltaTime) override;

		void Activate();

		void SetProjectionMode(EProjectionMode InProjectionMode);
		EProjectionMode GetProjectionMode() const;

		void SetFOV(float InFOV);
		float GetFOV() const;

		void SetPerspectiveWidth(float InWidth);
		float GetPerspectiveWidth() const;

		void SetPerspectiveHeight(float InHeight);
		float GetPerspectiveHeight() const;

		void SetPerspectiveMinZ(float InMinZ);
		float GetPerspectiveMinZ() const;

		void SetPerspectiveMaxZ(float InMaxZ);
		float GetPerspectiveMaxZ() const;

		void SetOrthographicWidth(float InWidth);
		float GetOrthographicWidth() const;

		void SetOrthographicHeight(float InHeight);
		float GetOrthographicHeight() const;

		void SetOrthographicZScale(float InZScale);
		float GetOrthographicZScale() const;

		void SetOrthographicZOffset(float InZOffset);
		float GetOrthographicZOffset() const;

	protected:
		EProjectionMode ProjectionMode = EProjectionMode::Perspective;
		PerspectiveProjectionData PerspectiveData;
		OrthographicProjectionData OrthographicData;

		float MinPitch = -90.0f;
		float MaxPitch = 90.0f;
	};
}