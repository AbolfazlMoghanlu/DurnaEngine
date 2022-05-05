#pragma once

#include <Runtime/Core/Application.h>


using namespace Durna;

namespace Durna
{
	class Actor;
	class StaticMeshActor;
	class PrimitiveComponent;
	class StaticMesh;
}


class GameApplication : public Durna::Application
{
public:
	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;

private:
	Actor* SkySphere = nullptr;
	PrimitiveComponent* SkyComponent;

	StaticMeshActor* WorldGizmo;

	Actor* Actor1;
 	PrimitiveComponent* pr1 = nullptr;
 	PrimitiveComponent* pr2 = nullptr;

	Durna::StaticMesh* SkyMesh;
	Durna::StaticMesh* CubeMesh;
};

