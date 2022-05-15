#pragma once

namespace Durna
{
	class Actor;

	class Component
	{
	public:
		Component(const std::string& InLabel);

		virtual void Tick(float DeltaTime);

		Actor* GetOwningActor() const;
		void SetOwningActor(Actor* InActor);

		bool IsActive() const;
		void SetActive(bool Active);

#if WITH_EDITOR
		std::string GetComponentLabel() const;
#endif

	private:
		Actor* Owner = nullptr;

		bool bActive = true;

#if WITH_EDITOR
		std::string ComponentLabel = "Component_00";
#endif
	};
}


