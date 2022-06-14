#pragma once

#include "Runtime/Components/SceneComponent.h"
#include "Runtime/Math/LinearColor.h"

namespace Durna
{
	class BillboardComponent;

	class SkyLightComponent : public SceneComponent
	{
	public:
		SkyLightComponent(const std::string& InLabel);
		virtual ~SkyLightComponent();

		float GetIntensity() const;
		void SetIntensity(float InIntensity);

		LinearColor GetLightColor() const;
		void SetLightColor(const LinearColor& InLightColor);

	protected:
		float Intensity = 1.0f;
		LinearColor LightColor = LinearColor::White;



	private:
		friend class SkyLightComponentPanel;
	};
}

