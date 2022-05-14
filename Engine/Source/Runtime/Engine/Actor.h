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
			
		void AttachSceneComponent(SceneComponent* InSceneComponent, SceneComponent* Target = nullptr);
		void AddComponent(Component* InComponent);

		SceneComponent* GetRoot() const;

		void MarkDestroy();
		bool IsMarkDestroy() const;

#if WITH_EDITOR
		virtual bool IsVisibleInWorldOutliner() { return true; };
		
		std::string GetActorLabel() const;
		void SetActorLabel(const std::string& InLabel);
#endif

	private:

		std::unique_ptr<SceneComponent> Root;

		/** this only contains non scene components */
		std::vector<Component*> Components;

		bool bDestroy = false;

#if WITH_EDITOR
		std::string ActorLabel = "Actor_00";
#endif
	};

}

