#include "DurnaPCH.h"
#include "SceneComponent.h"

#include "Runtime/Engine/Actor.h"

namespace Durna
{
	void SceneComponent::Tick(float DeltaTime)
	{
		Component::Tick(DeltaTime);

		UpdateLocation();

		for (SceneComponent* SceneComp : Childs)
		{
			Tick(DeltaTime);
		}
	}

	void SceneComponent::AttachSceneComponent(SceneComponent* InComponent)
	{
		InComponent->Parent = this;
		Childs.push_back(InComponent);
	}

	const std::vector<SceneComponent*>& SceneComponent::GetChilds() const
	{
		return Childs;
	}

	Vector3f SceneComponent::GetRelativeLocation()
	{
		return RelativeLocation;
	}

	Vector3f SceneComponent::GetWorldLocation()
	{
		return WorldLocation;
	}

	void SceneComponent::SetRelativeLocation(const Vector3f& Inlocation, bool bMarkDirty)
	{
		RelativeLocation = Inlocation;
		if (bMarkDirty)
		{
			MarkDirtyLocationRecursive();
		}
	}

	void SceneComponent::SetWorldLocation(const Vector3f& Inlocation, bool bMarkDirty /*= true*/)
	{
	}

	Vector3f SceneComponent::GetLocalLocation()
	{
		return LocalLocation;
	}

	void SceneComponent::UpdateLocation()
	{
		ensure(GetOwningActor(), "Invalid owner!");
		ensure(Parent, "Invalid parent!");

		if (bDirtyLocation)
		{
			LocalLocation = GetWorldLocation() - GetOwningActor()->GetActorLocation();
			WorldLocation = RelativeLocation + Parent->GetWorldLocation();

			bDirtyLocation = false;
		}
	}

	bool SceneComponent::IsDirtyLocation() const
	{
		return bDirtyLocation;
	}

	void SceneComponent::MarkDirtyLocation()
	{
		bDirtyLocation = true;
	}

	void SceneComponent::MarkDirtyLocationRecursive()
	{
		MarkDirtyLocation();

		for (SceneComponent* Comp : Childs)
		{
			Comp->MarkDirtyLocationRecursive();
		}
	}

}