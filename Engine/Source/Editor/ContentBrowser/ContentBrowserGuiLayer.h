#pragma once

#if WITH_EDITOR
#include "Runtime/Renderer/ImGui/ImGuiLayer.h"

namespace Durna
{
	class ContentBrowserGuiLayer : public ImGuiLayer
	{
	public:
		virtual void Draw() override;

	protected:

	private:
		bool bImportFileOpen = false;
		std::wstring CurrentDirectory = L"";

		void ShowToolbar();
		void ShowImportFileMenu();


		void OnClickedImprot();
	};
}

#endif