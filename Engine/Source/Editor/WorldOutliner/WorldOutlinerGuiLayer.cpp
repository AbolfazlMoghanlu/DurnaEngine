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
			if (It)
			{
				ImGui::Button(It->GetActorLabel().c_str());
				if (ImGui::IsItemClicked())
				{
					Editor::Get()->SetSelectedActor(*It);
				}
			}
		}

		ImGui::End();
	}
}
#endif