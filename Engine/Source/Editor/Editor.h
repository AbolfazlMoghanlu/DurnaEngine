#pragma once

namespace Durna
{
#if WITH_EDITOR

	class Actor;
	class SceneComponent;

	class Editor
	{
	public:
		Editor();
		~Editor();

		void Init();
		void Tick(float DeltaTime);

		static Editor* Get();

		void SetSelectedActor(Actor* InActor);
		void ClearSelectedActor();
		Actor* GetSelectedActor() const;

		void SetSelectedComponent(SceneComponent* InComponent);
		void ClearSelectedComponent();
		SceneComponent* GetSelectedComponent() const;

		bool IsComponentSelected(SceneComponent* InComponent) const;
		bool IsActorSelected(Actor* InActor) const;
		bool IsOwningActorSelected(SceneComponent* InComponent);
		bool bIsAnyActorSelected() const;
		bool bIsAnyComponentSelected() const;

	protected:

	private:
		static std::unique_ptr<Editor> SingletonInstance;

		Actor* SelectedActor = nullptr;
		SceneComponent* SelectedComponent = nullptr;
	};

#endif
}

