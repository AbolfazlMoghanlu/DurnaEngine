#include "DurnaPCH.h"
#include "Component.h"

#include "Runtime/Engine/Actor.h"

namespace Durna
{
	Component::Component(const std::string& InLabel)
	{
#if WITH_EDITOR
		ComponentLabel = InLabel;
#endif
	}

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

#if WITH_EDITOR
	std::string Component::GetComponentLabel() const
	{
		return ComponentLabel;
	}
#endif
}

