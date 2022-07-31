#pragma once

#if WITH_EDITOR
#include "Runtime/Renderer/ImGui/ImGuiLayer.h"
#include "Runtime/Misc/DiskDrive/DiskDriveTypes.h"


namespace Durna
{
	class FileMenu;

	class ContentBrowserGuiLayer : public ImGuiLayer
	{
	public:
		ContentBrowserGuiLayer();

		virtual void Draw() override;

	protected:

	private:
		std::unique_ptr<FileMenu> ImportFileMenu;

		void ShowToolbar();



		void OnClickedImprot();

		void OnImportCancel();
		void OnImportFiles(const std::vector<SystemFile>& Files);
	};
}

#endif