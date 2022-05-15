#include "DurnaPCH.h"
#include "Actor.h"

#include "Runtime/Math/Rotator.h"

namespace Durna
{
	Actor::Actor()
	{
		Root = std::make_unique<SceneComponent>("Root");
		Root->SetOwningActor(this);
	}

	Actor::~Actor()
	{
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
		return Root->GetWorldLocation();
	}

	void Actor::SetActorLocation(const Vector3f& InLocation)
	{
		return Root->SetWorldLocation(InLocation);
		Root->MarkDirtyLocationRecursive();
	}

	const Rotatorf& Actor::GetActorRotation()
	{
		return Root->GetWorldRotation();
	}

	void Actor::SetActorRotation(const Rotatorf& InRotator)
	{
		Root->WorldRotation = InRotator;
		Root->MarkDirtyRotationRecursive();
	}

	const Vector3f& Actor::GetActorScale()
	{
		return Root->GetWorldScale();
	}

	void Actor::SetActorScale(const Vector3f& InScale)
	{
		Root->WorldScale = InScale;
		Root->MarkDirtyScaleRecursive();
	}

	void Actor::AttachSceneComponent(SceneComponent* InSceneComponent, SceneComponent* Target)
	{
		if (!Target)
		{
			Target = Root.get();
		}

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
		return Root.get();
	}

	void Actor::MarkDestroy()
	{
		bDestroy = true;
	}

	bool Actor::IsMarkDestroy() const
	{
		return bDestroy;
	}

#if WITH_EDITOR
	std::string Actor::GetActorLabel() const
	{
		return ActorLabel;
	}

	void Actor::SetActorLabel(const std::string& InLabel)
	{
		ActorLabel = InLabel;
	}
#endif
}