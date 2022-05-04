#include "GameApplication.h"

#include <Durna.h>
#include <DurnaPCH.h>

#include "Runtime/Engine/Actor.h"
#include "Runtime/Components/PrimitiveComponent.h"
#include "Runtime/Engine/BaseShapes.h"
#include "Runtime/Assets/AssetLibrary.h"
#include "Runtime/Engine/Camera/CameraManager.h"
#include "Runtime/Renderer/Renderer.h"
#include "Runtime/Math/Math.h"
#include "Runtime/Engine/StaticMesh.h"
#include "Runtime/Misc/ModelLoader.h"


void GameApplication::Init()
{
	Application::Init();	

	SkyMesh = new Durna::StaticMesh;
	ModelLoader::Load(Path::ModelRelativePath("FlipedSphere.obj"), SkyMesh);

	CubeMesh = new Durna::StaticMesh;
	ModelLoader::Load(Path::ModelRelativePath("SphereSmooth.obj"), CubeMesh);

	SkyComponent = new PrimitiveComponent(SkyMesh, AssetLibrary::SkyMaterial);
	SkySphere = new Actor();
	SkySphere->AttachSceneComponent(SkyComponent, SkySphere->GetRoot());
	SkySphere->SetActorScale(Vector3f(100000.0f));
	SkySphere->SetActorRotation(Rotatorf(00.0f, 00.0f, 90.0f));

	pr = new PrimitiveComponent(CubeMesh, AssetLibrary::BaseMaterial);
	pr1 = new PrimitiveComponent(CubeMesh, AssetLibrary::BaseMaterial);

	Actor1 = new Actor();
	Actor1->AttachSceneComponent(pr, Actor1->GetRoot());
	Actor1->AttachSceneComponent(pr1, pr);

	Actor1->SetActorScale(Vector3f(100.0f));

	CameraManager::GetActiveCamera()->SetFOV(45.0);
	CameraManager::GetActiveCamera()->SetPerspectiveMinZ(0.1f);
	CameraManager::GetActiveCamera()->SetPerspectiveMaxZ(1000.0f);
}

void GameApplication::Tick(float DeltaTime)
{
	Application::Tick(DeltaTime);

	
	Actor1->SetActorLocation(Vector3f(1.0, 0, 0));

	pr1->SetRelativeLocation(Vector3f(Math::Sin(Renderer::GetTime()), Math::Cos(Renderer::GetTime()), 0.0f));
	pr1->SetRelativeRotation(Rotatorf(0.0f, Math::Cos(Renderer::GetTime()) * 360.0f, 0.0f));

	Actor1->Tick(DeltaTime);
	SkySphere->Tick(DeltaTime);
}
