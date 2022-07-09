#pragma once

#include <Runtime/Core/Application.h>

using namespace Durna;

namespace Durna
{
	class Actor;
	class StaticMeshActor;
	class PrimitiveComponent;
	class StaticMesh;
	class Texture;
	class Texture2D;
	class TextureCube;
	class PointLightComponent;
}


class GameApplication : public Durna::Application
{
public:
	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;

private:

	StaticMeshActor* WorldGizmo = nullptr;

	Actor* Actor1 = nullptr;
 	PrimitiveComponent* pr1 = nullptr;
 	PrimitiveComponent* pr2 = nullptr;
 	PrimitiveComponent* pr3 = nullptr;

	PointLightComponent* LightSource_1;
	PointLightComponent* LightSource_2;
	PointLightComponent* LightSource_3;

	Durna::StaticMesh* CubeMesh = nullptr;

	StaticMeshActor* RockActor = nullptr;

	StaticMeshActor* FloorActor = nullptr;
};

