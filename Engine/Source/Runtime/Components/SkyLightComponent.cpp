#include "DurnaPCH.h"
#include "SkyLightComponent.h"
#include "Runtime/Components/BillboardComponent.h"

#if WITH_EDITOR
#include "Editor/DetailsPanel/SkyLightComponentPanel.h"
#endif

namespace Durna
{
	SkyLightComponent::SkyLightComponent(const std::string& InLabel)
		: SceneComponent(InLabel)
	{ 
#if WITH_EDITOR
		Panel = new SkyLightComponentPanel(this);
#endif
	}

	SkyLightComponent::~SkyLightComponent()
	{
#if WITH_EDITOR
		delete Panel;
#endif
	}

	float SkyLightComponent::GetIntensity() const
	{
		return Intensity;
	}

	void SkyLightComponent::SetIntensity(float InIntensity)
	{
		Intensity = InIntensity;
	}

	LinearColor SkyLightComponent::GetLightColor() const
	{
		return LightColor;
	}

	void SkyLightComponent::SetLightColor(const LinearColor& InLightColor)
	{
		LightColor = InLightColor;
	}
}