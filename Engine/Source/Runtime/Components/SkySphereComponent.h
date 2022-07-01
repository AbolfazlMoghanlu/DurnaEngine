#pragma once

#include "Runtime/Components/PrimitiveComponent.h"
#include "Runtime/Math/LinearColor.h"

namespace Durna
{
	class Material;

	class SkySphereComponent : public PrimitiveComponent
	{
	public:
		SkySphereComponent(const std::string& InLabel);
		virtual ~SkySphereComponent();

		LinearColor GetOverallColor() const;
		void SetOverallColor(const LinearColor& InOverallColor);

	protected:
		LinearColor OverallColor = LinearColor::White;

		friend class SkySphereComponentPanel;
	};
}