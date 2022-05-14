#pragma once

namespace Durna
{
#if WITH_EDITOR

	class Actor;

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
		Actor* GetSelectedActor();

	protected:

	private:
		static std::unique_ptr<Editor> SingletonInstance;

		Actor* SelectedActor = nullptr;
	};

#endif
}

