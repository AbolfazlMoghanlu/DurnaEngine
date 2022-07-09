#pragma once

#include "Runtime/Components/SceneComponent.h"
#include "Runtime/Math/Color.h"
#include "Runtime/Math/LinearColor.h"
#include "Runtime/Math/Matrix.h"

namespace Durna
{
	class ShadowFrameBuffer;

	class LightComponent : public SceneComponent
	{
	public:
		LightComponent(const std::string& InLabel);
		virtual ~LightComponent();
		
		virtual void Tick(float DeltaTime) override;

		float GetIntensity() const;
		void SetIntensity(float InIntensity);

		LinearColor GetLightColor() const;
		void SetLightColor(const LinearColor& InColor);

		float GetAttenuation() const;
		void SetAttenuation(float InAttenuation);

		float GetMaxDrawDistance() const;
		void SetMaxDrawDistance(float InMaxDrawDistance);

		float GetMaxFadeRange() const;
		void SetMaxFadeRange(float InMaxFadeRange);

		int32 GetShadowResolution() const;
		void SetShadowResolution(int32 InShadowResolution);

		bool IsVisible();
		void SetVisiblity(bool InVisiblity);

		bool GetCastShadow() const;
		void SetCastShadow(bool Enabled);

		std::shared_ptr<ShadowFrameBuffer> GetShadowFrameBuffer();

		const Matrix<float>& GetViewMatrix() const;
		const Matrix<float>& GetProjectionMatrix() const;

		// TODO: add bias

	protected:
		float Intensity = 1.0f;
		LinearColor LightColor = LinearColor::White;
		float Attenuation = 1.0f;

		float MaxDrawDistance = 1.0f;
		float MaxFadeRange = 1.0f;

		int32 ShadowResolution = 1024;

		bool bVisible = true;
		bool bCastShadow = false;


	protected:
		Matrix<float> LightViewMatrix;
		Matrix<float> LightProjectionMatrix;

		virtual void UpdateViewMatrix() = 0;
		virtual void UpdateProjectionMatrix() = 0;

		std::shared_ptr<ShadowFrameBuffer> ShadowFBO;

		void RebuildShadowBuffer();

	private:
		// TODO: make matrices update only when light moves and is max draw distance
		bool bDirtyShadow = true;
	};
}