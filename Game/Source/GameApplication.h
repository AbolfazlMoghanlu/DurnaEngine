#pragma once

#include <Runtime/Core/Application.h>


using namespace Durna;

namespace Durna
{
	class Actor;
	class PrimitiveComponent;
	class StaticMesh;
}


class GameApplication : public Durna::Application
{
public:
	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;

private:
	Actor* Actor1 = nullptr;
 	PrimitiveComponent* pr = nullptr;
 	PrimitiveComponent* pr1 = nullptr;

	Actor* SkySphere = nullptr;
	PrimitiveComponent* Mesh;
	Durna::StaticMesh* FlipedSphere;
};

