#pragma once

#include "Runtime/Engine/Actor.h"

namespace Durna
{
	class PrimitiveComponent;
	class StaticMesh;

	class StaticMeshActor : public Actor
	{
	public:
		StaticMeshActor();
		virtual ~StaticMeshActor();

		virtual void Tick(float DeltaTime) override;

		PrimitiveComponent* GetMeshComponent() const;

	protected:
		std::unique_ptr<PrimitiveComponent> MeshComponent;
	};
}

