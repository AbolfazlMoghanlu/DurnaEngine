#pragma once

#include "Runtime/Components/Component.h"
#include "Runtime/Math/Vector3.h"

namespace Durna
{
	class SceneComponent : public Component
	{
	public:
		
		void Tick(float DeltaTime) override;

		void AttachSceneComponent(SceneComponent* InComponent);

		const std::vector<SceneComponent*>& GetChilds() const;

		Vector3f GetRelativeLocation();
		Vector3f GetLocalLocation();
		Vector3f GetWorldLocation();

		void SetRelativeLocation(const Vector3f& Inlocation, bool bMarkDirty = true);
		void SetWorldLocation(const Vector3f& Inlocation, bool bMarkDirty = true);

		void UpdateLocation();

		bool IsDirtyLocation() const;
		void MarkDirtyLocation();
		void MarkDirtyLocationRecursive();

	private:
		
		SceneComponent* Parent = nullptr;
		std::vector<SceneComponent*> Childs;

		Vector3f RelativeLocation	= Vector3f::ZeroVector;
		Vector3f LocalLocation		= Vector3f::ZeroVector;

	public:
		// TODO: make private
		Vector3f WorldLocation		= Vector3f::ZeroVector;

	private:
		bool bDirtyLocation = true;
	};

}

