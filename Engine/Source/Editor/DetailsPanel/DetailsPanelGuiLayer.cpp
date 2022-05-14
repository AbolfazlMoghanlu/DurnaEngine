#include "DurnaPCH.h"
#include "DetailsPanelGuiLayer.h"

#if WITH_EDITOR

#include "imgui.h"
#include "Editor/Editor.h"
#include "Runtime/Engine/Actor.h"

namespace Durna
{
	void DetailsPanelGuiLayer::Draw()
	{
		ImGui::Begin("DetailPanel");

		Actor* SelectedActor = Editor::Get()->GetSelectedActor();

		ImGui::Text(SelectedActor ? SelectedActor->GetActorLabel().c_str() : "Invalid Actor");

		std::stringstream LocationText;
		LocationText << "Location	X : ";
		LocationText << (SelectedActor ? SelectedActor->GetActorLocation().X : 0.0);
		LocationText << ", Y : ";
		LocationText << (SelectedActor ? SelectedActor->GetActorLocation().Y : 0.0);
		LocationText << ", Z : ";
		LocationText << (SelectedActor ? SelectedActor->GetActorLocation().Z : 0.0);
	
		ImGui::Text(LocationText.str().c_str());

		ImGui::End();
	}
}

#endif