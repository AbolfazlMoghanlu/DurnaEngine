#include "DurnaPCH.h"
#include "WorldOutlinerGuiLayer.h"

#include "Runtime/Engine/World.h"
#include "Runtime/Containers/List.h"
#include "Runtime/Engine/Actor.h"

#if WITH_EDITOR
#include "imgui.h"
#include "Editor/Editor.h"

namespace Durna
{
	void WorldOutlinerGuiLayer::Draw()
	{
		ImGui::Begin("World Outliner");

		for (LinkedListIterator It(World::Actors); It; ++It)
		{
			if (It && It->IsVisibleInWorldOutliner())
			{	
				bool bSelected = Editor::Get()->GetSelectedActor() == *It;
				if (bSelected)
				{
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0.65, 0, 1));
					bSelected = true;
				}
			
				ImGui::Button(It->GetActorLabel().c_str());

				if (ImGui::IsItemClicked())
				{
					if (bSelected)
					{
						Editor::Get()->ClearSelectedActor();
					}
					else
					{
						Editor::Get()->SetSelectedActor(*It);		
					}
				}

				if (bSelected)
				{
					ImGui::PopStyleColor(1);
				}
			}
		}

		ImGui::End();
	}
}
#endif