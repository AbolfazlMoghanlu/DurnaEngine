#pragma once

#include "Runtime/Components/SceneComponent.h"
#include "Runtime/Math/Vector3.h"

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
			
		void AttachSceneComponent(SceneComponent* InSceneComponent, SceneComponent* Target);
		void AddComponent(Component* InComponent);

		SceneComponent* GetRoot() const;

	private:

		SceneComponent* Root;

		/** this only contains non scene components */
		std::vector<Component*> Components;
	};

}

