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
		SceneComponent* SelectedComponent = Editor::Get()->GetSelectedComponent();

		if (SelectedActor)
		{
			ImGui::Text(SelectedActor->GetActorLabel().c_str());
			ImGui::Spacing();

			BuildComponents(SelectedActor);

			BuildTransformHeader(SelectedComponent ? SelectedComponent : SelectedActor->GetRoot());

			if (SelectedComponent && SelectedComponent->Panel != nullptr)
			{
				SelectedComponent->Panel->DrawPanel();
			}
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
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.65f, 0.0f, 1.0f));
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
			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, 80);

			// ------- location -------------------------
			ImGui::Text("Location");
			ImGui::NextColumn();
			ImGui::DragFloat3("##Location", &InSceneComponent->RelativeLocation.X, 0.1f, -1000.0f, 1000.0f);

			// if it's root then update it's world to relative
			if (InSceneComponent->Parent == nullptr)
			{
				InSceneComponent->WorldLocation = InSceneComponent->RelativeLocation;
			}

			InSceneComponent->MarkDirtyLocationRecursive();
			
			// ------- rotation -------------------------
			ImGui::NextColumn();
			ImGui::Text("Rotation");
			ImGui::NextColumn();

			ImGui::DragFloat3("##Rotation", &InSceneComponent->RelativeRotation.Pitch, 1.0f, -360.0f, 360.0f);

			// if it's root then update it's world to relative
			if (InSceneComponent->Parent == nullptr)
			{
				InSceneComponent->WorldRotation = InSceneComponent->RelativeRotation;
			}

			InSceneComponent->MarkDirtyRotationRecursive();

			
			// ------- scale -------------------------
			ImGui::NextColumn();
			ImGui::Text("Scale");
			ImGui::NextColumn();
			ImGui::DragFloat3("##Scale", &InSceneComponent->RelativeScale.X, 0.1f, -10.0f, 10.0f);
			ImGui::Columns(1);

			// if it's root then update it's world to relative
			if (InSceneComponent->Parent == nullptr)
			{
				InSceneComponent->WorldScale = InSceneComponent->RelativeScale;
			}

			InSceneComponent->MarkDirtyScaleRecursive();
		}
	}
}


#endif