#pragma once

#include "Runtime/Components/Component.h"
#include "Runtime/Math/Vector3.h"
#include "Runtime/Math/Rotator.h"

namespace Durna
{
	class SceneComponent : public Component
	{
	public:
		
		void Tick(float DeltaTime) override;

		void AttachSceneComponent(SceneComponent* InComponent);

		const std::vector<SceneComponent*>& GetChilds() const;

		// ------------------ location -----------------
		Vector3f GetRelativeLocation() const;
		Vector3f GetLocalLocation() const;
		Vector3f GetWorldLocation() const;

		void SetRelativeLocation(const Vector3f& Inlocation, bool bMarkDirty = true);
		void SetLocalLocation(const Vector3f& Inlocation, bool bMarkDirty = true);
		void SetWorldLocation(const Vector3f& Inlocation, bool bMarkDirty = true);

		void UpdateLocation();

		bool IsDirtyLocation() const;
		void MarkDirtyLocation();
		void MarkDirtyLocationRecursive();

		// ------------------ rotation --------------------
		Rotatorf GetRelativeRotation() const;
		Rotatorf GetLocalRotation() const;
		Rotatorf GetWorldRotation() const;

		void SetRelativeRotation(const Rotatorf& InRotator, bool bMarkDirty = true);
		void SetLocalRotation(const Rotatorf& InRotator, bool bMarkDirty = true);
		void SetWorldRotation(const Rotatorf& InRotator, bool bMarkDirty = true);

		void UpdateRotation();

		bool IsDirtyRotation() const;
		void MarkDirtyRotation();
		void MarkDirtyRotationRecursive();

		// ------------------ scale ------------------------
		Vector3f GetRelativeScale() const;
		Vector3f GetLocalScale() const;
		Vector3f GetWorldScale() const;

		void SetRelativeScale(const Vector3f& InScale, bool bMarkDirty = true);
		void SetLocalScale(const Vector3f& InScale, bool bMarkDirty = true);
		void SetWorldScale(const Vector3f& InScale, bool bMarkDirty = true);

		void UpdateScale();

		bool IsDirtyScale() const;
		void MarkDirtyScale();
		void MarkDirtyScaleRecursive();


	private:
		
		SceneComponent* Parent = nullptr;
		std::vector<SceneComponent*> Childs;

		Vector3f WorldLocation		= Vector3f::ZeroVector;
		Vector3f RelativeLocation	= Vector3f::ZeroVector;
		Vector3f LocalLocation		= Vector3f::ZeroVector;

		Rotatorf WorldRotation		= Rotatorf::ZeroRotator;
		Rotatorf RelativeRotation	= Rotatorf::ZeroRotator;
		Rotatorf LocalRotation		= Rotatorf::ZeroRotator;

		Vector3f WorldScale			= Vector3f::OneVector;
		Vector3f RelativeScale		= Vector3f::OneVector;
		Vector3f LocalScale			= Vector3f::OneVector;

		bool bDirtyLocation = true;
		bool bDirtyRotation = true;
		bool bDirtyScale	= true;

		friend class Actor;
	};

}

