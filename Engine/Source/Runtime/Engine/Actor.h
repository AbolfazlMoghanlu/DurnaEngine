#pragma once

#include "Runtime/Components/SceneComponent.h"
#include "Runtime/Math/Vector3.h"
#include "Runtime/Math/Rotator.h"

namespace Durna
{
	class SceneComponent;

	class Actor
	{
	public:

		Actor();
		~Actor();

		virtual void Tick(float DeltaTime);

		const Vector3f& GetActorLocation();
		void SetActorLocation(const Vector3f& InLocation);

		const Rotatorf& GetActorRotation();
		void SetActorRotation(const Rotatorf& InRotator);

		const Vector3f& GetActorScale();
		void SetActorScale(const Vector3f& InScale);
			
		void AttachSceneComponent(SceneComponent* InSceneComponent, SceneComponent* Target);
		void AddComponent(Component* InComponent);

		SceneComponent* GetRoot() const;

		void MarkDestroy();
		bool IsMarkDestroy() const;

	private:

		SceneComponent* Root;

		/** this only contains non scene components */
		std::vector<Component*> Components;

		bool bDestroy = false;
	};

}

