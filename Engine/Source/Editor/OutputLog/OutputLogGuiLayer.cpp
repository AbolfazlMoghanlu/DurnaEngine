#include "DurnaPCH.h"
#include "OutputLogGuiLayer.h"


#if WITH_EDITOR

#include "Editor/OutputLog/OutputLog.h"
#include "imgui.h"

namespace Durna
{
	void OutputLogGuiLayer::Draw()
	{
		const std::vector<LogMessage>& Logs = OutputLog::Get()->GetLogMessages();
		
		ImGui::Begin("OutputLog", (bool*)0, ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);
		MakeMenuBar();
		MakeLogsTable();
		ImGui::End();
	}

	void OutputLogGuiLayer::MakeMenuBar()
	{
		if (ImGui::BeginMenuBar())
		{
			// variant verbosities can toggled off and on
			if (ImGui::BeginMenu("Verbosity"))
			{
				if (ImGui::MenuItem("Info", NULL, OutputLog::Get()->bInfoLogEnabled))
				{
					OutputLog::Get()->bInfoLogEnabled = !OutputLog::Get()->bInfoLogEnabled;
				}

				if (ImGui::MenuItem("Warning", NULL, OutputLog::Get()->bWarningLogEnabled))
				{
					OutputLog::Get()->bWarningLogEnabled = !OutputLog::Get()->bWarningLogEnabled;
				}

				if (ImGui::MenuItem("Error", NULL, OutputLog::Get()->bErrorLogEnabled))
				{
					OutputLog::Get()->bErrorLogEnabled = !OutputLog::Get()->bErrorLogEnabled;
				}

				ImGui::EndMenu();
			}

			// list of all available categories, they can be toggled off and on
			if (ImGui::BeginMenu("Categories"))
			{
				for (LogCategory* Cat : OutputLog::Get()->LogCategories)
				{
					if (ImGui::MenuItem(Cat->Name, NULL, !Cat->Suppressed))
					{
						Cat->Suppressed = !Cat->Suppressed;
					}
				}

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
	}

	void OutputLogGuiLayer::MakeLogsTable()
	{
		const std::vector<LogMessage>& Logs = OutputLog::Get()->GetLogMessages();
		std::vector<int32> QualifiedLogs;
		GetQualifiedLogsIndex(QualifiedLogs);

		ImVec2 outer_size = ImGui::GetContentRegionAvail();
		static ImGuiTableFlags flags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg |
			ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable |
			ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;

		if (ImGui::BeginTable("OutputLogTable", 3, flags, outer_size))
		{
			ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
			ImGui::TableSetupColumn("Time", ImGuiTableColumnFlags_None);
			ImGui::TableSetupColumn("Category", ImGuiTableColumnFlags_None);
			ImGui::TableSetupColumn("Message", ImGuiTableColumnFlags_None);
			ImGui::TableHeadersRow();



			// make list for visible logs
			ImGuiListClipper clipper;
			clipper.Begin(QualifiedLogs.size());
			while (clipper.Step())
			{
				for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
				{
					ImGui::TableNextRow();

					switch (Logs[QualifiedLogs[row]].VerboseLevel)
					{
					case Verbosity::Error: ImGui::PushStyleColor(0, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); break;
					case Verbosity::Warning: ImGui::PushStyleColor(0, ImVec4(1.0f, 1.0f, 0.0f, 1.0f)); break;
					case Verbosity::Info:
					default:
						ImGui::PushStyleColor(0, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
					}

					ImGui::TableSetColumnIndex(0);
					ImGui::Text(Logs[QualifiedLogs[row]].Time.ToString().c_str());

					ImGui::TableSetColumnIndex(1);
					ImGui::Text(Logs[QualifiedLogs[row]].Category->Name);

					ImGui::TableSetColumnIndex(2);
					ImGui::Text(Logs[QualifiedLogs[row]].Message.c_str());

					ImGui::PopStyleColor(1);
				}
			}

			// if scroll is on end of table keep it on the end
			if (ImGui::GetScrollMaxY() - 100 < ImGui::GetScrollY())
			{
				ImGui::SetScrollY(ImGui::GetScrollMaxY());
			}

			ImGui::EndTable();
		}
	}

	void OutputLogGuiLayer::GetQualifiedLogsIndex(std::vector<int32>& Indices)
	{
		const std::vector<LogMessage>& Logs = OutputLog::Get()->GetLogMessages();

		Indices.clear();
		Indices.reserve(Logs.size());

		for (int32 i = 0; i < Logs.size(); i++)
		{
			const LogMessage& Msg = Logs[i];

			if (Msg.Category->Suppressed)
			{
				continue;
			}

			if (Msg.VerboseLevel == Verbosity::Info && OutputLog::Get()->bInfoLogEnabled)
			{
				Indices.push_back(i);
				continue;
			}

			else if (Msg.VerboseLevel == Verbosity::Warning && OutputLog::Get()->bWarningLogEnabled)
			{
				Indices.push_back(i);
				continue;
			}

			else if (Msg.VerboseLevel == Verbosity::Error && OutputLog::Get()->bErrorLogEnabled)
			{
				Indices.push_back(i);
				continue;
			}
		}
	}
}

#endif