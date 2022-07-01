#pragma once

#if WITH_EDITOR

#include "Editor/DetailsPanel/DetailPanelInterface.h"
#include "Runtime/Math/LinearColor.h"

namespace Durna
{
	class SkySphereComponent;

	class SkySphereComponentPanel : public DetailPanelInterface
	{
	public:
		SkySphereComponentPanel(SkySphereComponent* InTarget);

		virtual void DrawPanel() override;

	protected:
		SkySphereComponent* Target;
	};
}

#endif