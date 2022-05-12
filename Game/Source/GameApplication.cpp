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
#include "Runtime/Engine/World.h"
#include "Runtime/Engine/GameFramwork/StaticMeshActor.h"
#include "Runtime/Renderer/CommonRenderUniforms.h"
#include "Runtime/Renderer/Material.h"

#include "Runtime/Engine/Camera/CameraActor.h"
#include "Runtime/Engine/Camera/CameraComponent.h"


#include "Runtime/Renderer/Shader.h"

void GameApplication::Init()
{
	Application::Init();	

	SkyMesh = new Durna::StaticMesh;
	ModelLoader::Load(Path::ModelRelativePath("FlipedSphere.obj"), SkyMesh);

	CubeMesh = new Durna::StaticMesh;
	ModelLoader::Load(Path::ModelRelativePath("SphereSmooth.obj"), CubeMesh);

	SkyComponent = new PrimitiveComponent();
	SkyComponent->SetStaticMesh(SkyMesh, true);
	SkyComponent->GetMaterial()->SetShader(AssetLibrary::SkyShader);
	SkyComponent->GetMaterial()->AddTextureElement(TextureElement("SkyTexture", AssetLibrary::SkyTexture));

	SkySphere = new Actor();
	SkySphere->AttachSceneComponent(SkyComponent, SkySphere->GetRoot());
	SkySphere->SetActorScale(Vector3f(100.0f));
	SkySphere->SetActorRotation(Rotatorf(00.0f, 00.0f, 90.0f));
	World::AddActor(SkySphere);

	WorldGizmo = new StaticMeshActor();
	WorldGizmo->GetMeshComponent()->SetStaticMesh(AssetLibrary::GizmoMesh, 1);
	WorldGizmo->GetMeshComponent()->GetMaterial()->SetShader(AssetLibrary::GizmoShader);
	WorldGizmo->GetMeshComponent()->GetMaterial()->AddTextureElement(TextureElement("BaseColor", AssetLibrary::RgbTexture));
	WorldGizmo->GetMeshComponent()->BindPreDraw(
		[](PrimitiveComponent* InComponent, Shader* InShader)
		{
			CommonRenderUniforms::UploadCameraLocation(InShader);
			InShader->SetUniformVec3f("ActorLocation", InComponent->GetOwningActor()->GetActorLocation());
		});
	WorldGizmo->GetMeshComponent()->SetRelativeScale(Vector3f(0.1f));
	World::AddActor(WorldGizmo);
	
	pr1 = new PrimitiveComponent();
	pr1->SetStaticMesh(CubeMesh, true, true, true);
	pr1->GetMaterial()->SetShader(AssetLibrary::BaseShader);
	pr1->GetMaterial()->AddTextureElement(TextureElement("texture1", AssetLibrary::TileTexture));
	pr1->GetMaterial()->AddTextureElement(TextureElement("texture2", AssetLibrary::WallTexture));

	pr2 = new PrimitiveComponent();
	pr2->SetStaticMesh(CubeMesh, true, true, true);
	pr2->GetMaterial()->SetShader(AssetLibrary::BaseShader);
	pr2->GetMaterial()->AddTextureElement(TextureElement("texture1", AssetLibrary::TileTexture));
	pr2->GetMaterial()->AddTextureElement(TextureElement("texture2", AssetLibrary::WallTexture));


	Actor1 = new Actor;
	Actor1->AttachSceneComponent(pr1);
	Actor1->AttachSceneComponent(pr2, pr1);

	Actor1->SetActorScale(Vector3f(0.1f));
	World::AddActor(Actor1);

	CameraActor* CameraAct = new CameraActor;

	CameraAct->GetCameraComponent()->SetFOV(45.0);
	CameraAct->GetCameraComponent()->SetPerspectiveMinZ(0.1f);
	CameraAct->GetCameraComponent()->SetPerspectiveMaxZ(1000.0f);
	CameraAct->GetCameraComponent()->SetWorldLocation(Vector3f(-1, 0, .25));

	World::AddActor(CameraAct);

	CameraAct->GetCameraComponent()->Activate();
}

void GameApplication::Tick(float DeltaTime)
{
	Application::Tick(DeltaTime);

	pr1->SetRelativeLocation(Vector3f(1.0, 0, 0));

	pr2->SetRelativeLocation(Vector3f(Math::Sin(Renderer::GetTime()), Math::Cos(Renderer::GetTime()), 0.0f));
	pr2->SetRelativeRotation(Rotatorf(0.0f, Math::Cos(Renderer::GetTime()) * 360.0f, 0.0f));

	
}
