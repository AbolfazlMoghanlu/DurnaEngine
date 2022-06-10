#include "DurnaPCH.h"
#include "LightComponent.h"
#include "Runtime/Renderer/FrameBuffer/ShadowFrameBuffer.h"

namespace Durna
{
	LightComponent::LightComponent(const std::string& InLabel) 
		: SceneComponent(InLabel)
	{ }

	LightComponent::~LightComponent()
	{ }

	void LightComponent::Tick(float DeltaTime)
	{
		SceneComponent::Tick(DeltaTime);

		UpdateViewMatrix();
		UpdateProjectionMatrix();
	}

	float LightComponent::GetIntensity() const
	{
		return Intensity;
	}

	void LightComponent::SetIntensity(float InIntensity)
	{
		Intensity = InIntensity;
	}

	LinearColor LightComponent::GetLightColor() const
	{
		return LightColor;
	}

	void LightComponent::SetLightColor(const LinearColor& InColor)
	{
		LightColor = InColor;
	}

	float LightComponent::GetMaxDrawDistance() const
	{
		return MaxDrawDistance;
	}

	void LightComponent::SetMaxDrawDistance(float InMaxDrawDistance)
	{
		MaxDrawDistance = InMaxDrawDistance;
	}

	float LightComponent::GetMaxFadeRange() const
	{
		return MaxFadeRange;
	}

	void LightComponent::SetMaxFadeRange(float InMaxFadeRange)
	{
		MaxFadeRange = InMaxFadeRange;
	}

	int32 LightComponent::GetShadowResolution() const
	{
		return ShadowResolution;
	}

	void LightComponent::SetShadowResolution(int32 InShadowResolution)
	{
		ShadowResolution = InShadowResolution;
		RebuildShadowBuffer();
	}

	bool LightComponent::IsVisible()
	{
		return bVisible;
	}

	void LightComponent::SetVisiblity(bool InVisiblity)
	{
		bVisible = InVisiblity;
	}

	bool LightComponent::GetCastShadow() const
	{
		return bCastShadow;
	}

	void LightComponent::SetCastShadow(bool Enabled)
	{
		bCastShadow = Enabled;

		if (bCastShadow)
		{
		RebuildShadowBuffer();	
		}
		else
		{
			ShadowFBO.reset();
		}
	}

	std::shared_ptr<ShadowFrameBuffer> LightComponent::GetShadowFrameBuffer()
	{
		return ShadowFBO;
	}

	const Matrix<float>& LightComponent::GetViewMatrix() const
	{
		return LightViewMatrix;
	}

	const Matrix<float>& LightComponent::GetProjectionMatrix() const
	{
		return LightProjectionMatrix;
	}

	void LightComponent::RebuildShadowBuffer()
	{
		ShadowFBO = std::make_shared<ShadowFrameBuffer>();
		ShadowFBO->SetSize(ShadowResolution, ShadowResolution);
	}
}