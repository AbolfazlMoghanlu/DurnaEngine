#include "DurnaPCH.h"
#include "Component.h"

#include "Runtime/Engine/Actor.h"

namespace Durna
{
	void Component::Tick(float DeltaTime)
	{

	}

	Actor* Component::GetOwningActor() const
	{
		return Owner;
	}

	void Component::SetOwningActor(Actor* InActor)
	{
		Owner = InActor;
	}

	bool Component::IsActive() const
	{
		return bActive;
	}

	void Component::SetActive(bool Active)
	{
		bActive = Active;
	}
}

