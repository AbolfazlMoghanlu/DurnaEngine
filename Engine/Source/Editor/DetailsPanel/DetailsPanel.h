#pragma once

#if WITH_EDITOR

#include "Editor/Editor.h"

namespace Durna
{
	class DetailsPanelGuiLayer;

	class DetailsPanel
	{
	public:
		DetailsPanel();
		~DetailsPanel();

		void Init();
		void Tick(float DeltaTime);

		static DetailsPanel* Get();

	protected:
		std::unique_ptr<DetailsPanelGuiLayer> DetailsPanelGui;

	private:
		static std::unique_ptr<DetailsPanel> SingletonInstance;
	};
}

#endif