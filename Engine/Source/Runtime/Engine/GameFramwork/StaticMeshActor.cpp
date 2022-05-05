#include "DurnaPCH.h"
#include "StaticMeshActor.h"

#include "Runtime/Components/PrimitiveComponent.h"
#include "Runtime/Engine/StaticMesh.h"

namespace Durna
{
	StaticMeshActor::StaticMeshActor() : Actor()
	{
		MeshComponent = new PrimitiveComponent;
		this->AttachSceneComponent(MeshComponent, GetRoot());
	}

	StaticMeshActor::~StaticMeshActor()
	{
		delete MeshComponent;
	}

	void StaticMeshActor::Tick(float DeltaTime)
	{
		Actor::Tick(DeltaTime);


	}

	PrimitiveComponent* StaticMeshActor::GetMeshComponent() const
	{
		return MeshComponent;
	}
}