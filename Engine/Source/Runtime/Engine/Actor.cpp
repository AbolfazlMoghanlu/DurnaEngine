#include "DurnaPCH.h"
#include "Actor.h"

#include "Runtime/Math/Rotator.h"

namespace Durna
{
	Actor::Actor()
	{
		Root = new SceneComponent();
		Root->SetOwningActor(this);
	}

	Actor::~Actor()
	{
		delete Root;
	}

	void Actor::Tick(float DeltaTime)
	{
		for (Component* Comp : Components)
		{
			Comp->Tick(DeltaTime);
		}

		for (SceneComponent* SceneComp : Root->GetChilds())
		{
			SceneComp->Tick(DeltaTime);
		}
	}

	const Vector3f& Actor::GetActorLocation()
	{
		return Root->WorldLocation;
	}

	void Actor::SetActorLocation(const Vector3f& InLocation)
	{
		Root->WorldLocation = InLocation;
		Root->MarkDirtyLocationRecursive();
	}

	void Actor::AttachSceneComponent(SceneComponent* InSceneComponent, SceneComponent* Target)
	{
		if (Target->GetOwningActor() == this)
		{
			Target->AttachSceneComponent(InSceneComponent);
			InSceneComponent->SetOwningActor(this);
		}
	}

	void Actor::AddComponent(Component* InComponent)
	{
		Components.push_back(InComponent);
		InComponent->SetOwningActor(this);
	}

	SceneComponent* Actor::GetRoot() const
	{
		return Root;
	}

}