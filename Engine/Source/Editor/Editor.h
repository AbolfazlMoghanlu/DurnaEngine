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

	protected:

	private:
		static std::unique_ptr<Editor> SingletonInstance;

		Actor* SelectedActor = nullptr;
		SceneComponent* SelectedComponent = nullptr;
	};

#endif
}

