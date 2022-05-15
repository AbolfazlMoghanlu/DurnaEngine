#include "DurnaPCH.h"
#include "DetailsPanelGuiLayer.h"

#if WITH_EDITOR

#include "imgui.h"
#include "Editor/Editor.h"
#include "Runtime/Engine/Actor.h"
#include "Runtime/Components/Component.h"
#include "Runtime/Components/SceneComponent.h"
#include "Runtime/Math/Vector3.h"

namespace Durna
{
	void DetailsPanelGuiLayer::Draw()
	{
		ImGui::Begin("DetailPanel");

		Actor* SelectedActor = Editor::Get()->GetSelectedActor();

		if (SelectedActor)
		{
			ImGui::Text(SelectedActor->GetActorLabel().c_str());
			ImGui::Spacing();

			BuildComponents(SelectedActor);

			BuildTransformHeader(Editor::Get()->GetSelectedComponent() ?
				Editor::Get()->GetSelectedComponent() : SelectedActor->GetRoot());
		}
		
		ImGui::End();
	}

	void DetailsPanelGuiLayer::BuildComponents(Actor* InActor)
	{
		if (ImGui::CollapsingHeader("Components", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
		{
			BuildComponentListRecursive(InActor->GetRoot());
		}
	}

	void DetailsPanelGuiLayer::BuildComponentListRecursive(SceneComponent* InSceneComponent)
	{
		for (SceneComponent* Comp : InSceneComponent->GetChilds())
		{
			if (Comp)
			{
				BuildComponent(Comp);
				BuildComponentListRecursive(Comp);
			}
		}
	}

	void DetailsPanelGuiLayer::BuildComponent(SceneComponent* InComponent)
	{
		bool bSelected = Editor::Get()->GetSelectedComponent() == InComponent;
		if (bSelected)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0.65, 0, 1));
		}

		ImGui::Button(InComponent->GetComponentLabel().c_str());

		if (ImGui::IsItemClicked())
		{
			if (bSelected)
			{
				Editor::Get()->ClearSelectedComponent();
			}
			else
			{
				Editor::Get()->SetSelectedComponent(InComponent);
			}
		}

		if (bSelected)
		{
			ImGui::PopStyleColor(1);
		}

	}

	void DetailsPanelGuiLayer::BuildTransformHeader(SceneComponent* InSceneComponent)
	{
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
		{
			std::stringstream LocationText;
			LocationText << "Location	";
			LocationText << InSceneComponent->GetRelativeLocation().ToString();
			ImGui::Text(LocationText.str().c_str());

			std::stringstream RotationText;
			RotationText << "Location	";
			RotationText << InSceneComponent->GetRelativeRotation().ToString();
			ImGui::Text(RotationText.str().c_str());

			std::stringstream ScaleText;
			ScaleText << "Location	";
			ScaleText << InSceneComponent->GetRelativeScale().ToString();
			ImGui::Text(ScaleText.str().c_str());
		}
	}
}

#endif