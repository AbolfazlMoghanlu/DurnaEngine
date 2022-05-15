#pragma once

#if WITH_EDITOR

#include "Runtime/Renderer/ImGui/ImGuiLayer.h"

namespace Durna
{
	class Actor;
	class Component;
	class SceneComponent;
	
	class DetailsPanelGuiLayer : public ImGuiLayer
	{
	public:
		virtual void Draw() override;

	protected:
		void BuildComponents(Actor* InActor);
		void BuildComponentListRecursive(SceneComponent* InSceneComponent);
		void BuildComponent(SceneComponent* InComponent);
		void BuildTransformHeader(SceneComponent* InSceneComponent);

	private:

	};
}

#endif