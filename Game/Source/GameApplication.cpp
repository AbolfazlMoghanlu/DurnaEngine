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

void GameApplication::Init()
{
	Application::Init();

	pr = new PrimitiveComponent(&BaseShapes::Cube, AssetLibrary::BaseMaterial);
	pr1 = new PrimitiveComponent(&BaseShapes::Cube, AssetLibrary::BaseMaterial);

	Actor1 = new Actor();
	Actor1->AttachSceneComponent(pr, Actor1->GetRoot());
	Actor1->AttachSceneComponent(pr1, pr);

	CameraManager::GetActiveCamera()->SetFOV(45);
}

void GameApplication::Tick(float DeltaTime)
{
	Application::Tick(DeltaTime);

	
	Actor1->SetActorLocation(Vector3f(2.5, 0, 0));

	pr1->SetRelativeLocation(Vector3f(Math::Sin(Renderer::GetTime()), Math::Cos(Renderer::GetTime()), 0.0f));
	pr1->SetRelativeRotation(Rotatorf(0.0f, Math::Cos(Renderer::GetTime()) * 360.0f, 0.0f));
	pr1->SetRelativeScale(Vector3f(Math::Sin(Renderer::GetTime()) / 2.0f + 0.5f));

	Actor1->Tick(DeltaTime);
}
