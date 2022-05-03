#include "DurnaPCH.h"
#include "SceneComponent.h"

#include "Runtime/Engine/Actor.h"

namespace Durna
{
	void SceneComponent::Tick(float DeltaTime)
	{
		Component::Tick(DeltaTime);

		UpdateLocation();
		UpdateRotation();
		UpdateScale();

		for (SceneComponent* SceneComp : Childs)
		{
			SceneComp->Tick(DeltaTime);
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

	const Vector3f& SceneComponent::GetRelativeLocation() const
	{
		return RelativeLocation;
	}

	const Vector3f& SceneComponent::GetLocalLocation() const
	{
		return LocalLocation;
	}

	const Vector3f& SceneComponent::GetWorldLocation()const
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

	void SceneComponent::SetLocalLocation(const Vector3f& Inlocation, bool bMarkDirty /*= true*/)
	{

	}

	void SceneComponent::SetWorldLocation(const Vector3f& Inlocation, bool bMarkDirty /*= true*/)
	{
	}

	void SceneComponent::UpdateLocation()
	{
		ensure(GetOwningActor(), "Invalid owner!");
		ensure(Parent, "Invalid parent!");

		if (bDirtyLocation)
		{
			WorldLocation = RelativeLocation + Parent->GetWorldLocation();
			LocalLocation = WorldLocation - GetOwningActor()->GetActorLocation();

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

	const Rotatorf& SceneComponent::GetRelativeRotation() const
	{
		return RelativeRotation;
	}

	const Rotatorf& SceneComponent::GetLocalRotation() const
	{
		return LocalRotation;
	}

	const Rotatorf& SceneComponent::GetWorldRotation() const
	{
		return WorldRotation;
	}

	void SceneComponent::SetRelativeRotation(const Rotatorf& InRotator, bool bMarkDirty /*= true*/)
	{
		RelativeRotation = InRotator;
		if (bMarkDirty)
		{
			MarkDirtyRotationRecursive();
		}
	}

	void SceneComponent::SetLocalRotation(const Rotatorf& InRotator, bool bMarkDirty /*= true*/)
	{

	}

	void SceneComponent::SetWorldRotation(const Rotatorf& InRotator, bool bMarkDirty /*= true*/)
	{

	}

	void SceneComponent::UpdateRotation()
	{
		ensure(GetOwningActor(), "Invalid owner!");
		ensure(Parent, "Invalid parent!");

		if (bDirtyRotation)
		{
			WorldRotation = RelativeRotation + Parent->GetWorldRotation();
			LocalRotation = Rotatorf::CombineRotators(WorldRotation, GetOwningActor()->GetActorRotation() * -1);

			bDirtyRotation = false;
		}
	}

	bool SceneComponent::IsDirtyRotation() const
	{
		return bDirtyRotation;
	}

	void SceneComponent::MarkDirtyRotation()
	{
		bDirtyRotation = true;
	}

	void SceneComponent::MarkDirtyRotationRecursive()
	{
		MarkDirtyRotation();

		for (SceneComponent* Comp : Childs)
		{
			Comp->MarkDirtyRotationRecursive();
		}
	}

	const Vector3f& SceneComponent::GetRelativeScale() const
	{
		return RelativeScale;
	}

	const Vector3f& SceneComponent::GetLocalScale() const
	{
		return LocalScale;
	}

	const Vector3f& SceneComponent::GetWorldScale() const
	{
		return WorldScale;
	}

	void SceneComponent::SetRelativeScale(const Vector3f& InScale, bool bMarkDirty /*= true*/)
	{
		RelativeScale = InScale;

		if (bMarkDirty)
		{
			MarkDirtyScaleRecursive();
		}
	}

	void SceneComponent::SetLocalScale(const Vector3f& InScale, bool bMarkDirty /*= true*/)
	{

	}

	void SceneComponent::SetWorldScale(const Vector3f& InScale, bool bMarkDirty /*= true*/)
	{

	}

	void SceneComponent::UpdateScale()
	{
		ensure(GetOwningActor(), "Invalid owner!");
		ensure(Parent, "Invalid parent!");

		if (bDirtyScale)
		{
			WorldScale = RelativeScale * Parent->GetWorldScale();
			LocalScale = WorldScale / GetOwningActor()->GetActorScale();

			bDirtyScale = false;
		}
	}

	bool SceneComponent::IsDirtyScale() const
	{
		return bDirtyScale;
	}

	void SceneComponent::MarkDirtyScale()
	{
		bDirtyScale = true;
	}

	void SceneComponent::MarkDirtyScaleRecursive()
	{
		MarkDirtyScale();

		for (SceneComponent* Comp : Childs)
		{
			Comp->MarkDirtyScaleRecursive();
		}
	}

}