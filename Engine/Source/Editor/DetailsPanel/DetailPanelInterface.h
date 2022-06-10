#pragma once

#if WITH_EDITOR

namespace Durna
{
	class DetailPanelInterface
	{
	public:
		virtual void DrawPanel() = 0;
	};
}

#endif