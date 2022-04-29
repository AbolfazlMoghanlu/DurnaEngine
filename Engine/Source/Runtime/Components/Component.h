#pragma once

namespace Durna
{
	class Actor;

	class Component
	{
	public:
		virtual void Tick(float DeltaTime);

		Actor* GetOwningActor() const;
		void SetOwningActor(Actor* InActor);

		bool IsActive() const;
		void SetActive(bool Active);

	private:
		Actor* Owner = nullptr;

		bool bActive = true;
	};
}


