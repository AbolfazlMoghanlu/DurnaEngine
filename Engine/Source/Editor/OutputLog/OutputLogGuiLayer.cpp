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
			for (const LogMessage& Msg : OutputLog::Get()->GetLogMessages())
			{
				ImGui::Text(Msg.Message.c_str());
			}
		}

		ImGui::End();
	}

}

#endif