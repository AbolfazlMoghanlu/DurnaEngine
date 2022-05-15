#include "DurnaPCH.h"
#include "StaticMeshActor.h"

#include "Runtime/Components/PrimitiveComponent.h"
#include "Runtime/Engine/StaticMesh.h"

namespace Durna
{
	StaticMeshActor::StaticMeshActor() : Actor()
	{
		MeshComponent = std::make_unique<PrimitiveComponent>("Mesh");
		this->AttachSceneComponent(MeshComponent.get());
	}

	StaticMeshActor::~StaticMeshActor()
	{ }

	void StaticMeshActor::Tick(float DeltaTime)
	{
		Actor::Tick(DeltaTime);


	}

	PrimitiveComponent* StaticMeshActor::GetMeshComponent() const
	{
		return MeshComponent.get();
	}
}