#pragma once

#include "Runtime/Components/PrimitiveComponent.h"
#include "Runtime/Math/LinearColor.h"

namespace Durna
{
	class Material;
	class Texture;

	class SkySphereComponent : public PrimitiveComponent
	{
	public:
		SkySphereComponent(const std::string& InLabel);
		virtual ~SkySphereComponent();

		LinearColor GetOverallColor() const;
		void SetOverallColor(const LinearColor& InOverallColor);

		Texture* GetCubemap() const;
		void SetCubemap(Texture* InTexture);

	protected:
		LinearColor OverallColor = LinearColor::White;
		Texture* Cubemap;

		friend class SkySphereComponentPanel;
	};
}