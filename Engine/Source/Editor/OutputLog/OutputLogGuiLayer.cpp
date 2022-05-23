#include "DurnaPCH.h"
#include "OutputLogGuiLayer.h"


#if WITH_EDITOR

#include "Editor/OutputLog/OutputLog.h"
#include "imgui.h"

namespace Durna
{
	void OutputLogGuiLayer::Draw()
	{
		ImGui::Begin("OutputLog");

		if (OutputLog::Get())
		{
			for (const std::string& str : OutputLog::Get()->Logs)
			{
				ImGui::Text(str.c_str());
			}
		}

		ImGui::End();
	}

}

#endif