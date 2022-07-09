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
#include "Runtime/Engine/GameFramwork/GameSettings.h"

#include "Runtime/Engine/Camera/CameraActor.h"
#include "Runtime/Engine/Camera/CameraComponent.h"
#include "Runtime/Renderer/RenderCommands.h"

#include "Runtime/Renderer/Texture.h"
#include "Runtime/Renderer/Texture2D.h"
#include "Runtime/Renderer/TextureCube.h"

#include "Runtime/Components/Light/PointLightComponent.h"

#include "Runtime/Renderer/Shader.h"
#include "Runtime/Renderer/ImGui/ImGuiRenderer.h"

LOG_DEFINE_CATEGORY(LogTest, "Test");

void GameApplication::Init()
{
	Application::Init();	

	CubeMesh = new Durna::StaticMesh;
	ModelLoader::Load(Path::ModelRelativePath("SphereSmooth.obj"), CubeMesh, 0, 0, 1);


	WorldGizmo = new StaticMeshActor();
	WorldGizmo->GetMeshComponent()->SetStaticMesh(AssetLibrary::GizmoMesh, 1, 1);
	WorldGizmo->GetMeshComponent()->GetMaterial()->SetShader(AssetLibrary::GizmoShader);
	WorldGizmo->GetMeshComponent()->GetMaterial()->AddTextureElement(TextureElement("BaseColor", AssetLibrary::RgbTexture));
	WorldGizmo->GetMeshComponent()->GetMaterial()->SetShadingModel(EShadingModel::Unlit);
	WorldGizmo->GetMeshComponent()->BindPreDraw(
		[](PrimitiveComponent* InComponent, Shader* InShader)
		{
			CommonRenderUniforms::UploadCameraLocation(InShader);
			InShader->SetUniformVec3f("ActorLocation", InComponent->GetOwningActor()->GetActorLocation());
		});
	WorldGizmo->GetMeshComponent()->SetRelativeScale(Vector3f(0.1f));
	WorldGizmo->GetMeshComponent()->SetCastShadow(false);

#if WITH_EDITOR
	WorldGizmo->SetActorLabel("WorldGizmo");
#endif

	World::Get()->AddActor(WorldGizmo);
	
	pr1 = new PrimitiveComponent("PrimitiveComponent_1");
	pr1->SetStaticMesh(CubeMesh, 1, 1);
	pr1->GetMaterial()->SetShader(AssetLibrary::BaseShader);
	pr1->GetMaterial()->AddTextureElement(TextureElement("texture1", AssetLibrary::TileTexture));
	pr1->GetMaterial()->AddTextureElement(TextureElement("texture2", AssetLibrary::WallTexture));
	pr1->StencilValue = 32;
	pr1->StencilMask = StencilMaskBitfield::Bit_6;
	pr1->BindPreDraw(
		[](PrimitiveComponent* InComponent, Shader* InShader)
		{
			InShader->SetUniform1f("Specular", 0.5f);
		});

	pr2 = new PrimitiveComponent("PrimitiveComponent_2");
	pr2->SetStaticMesh(CubeMesh, 1, 1);
	pr2->GetMaterial()->SetShader(AssetLibrary::BaseShader);
	pr2->GetMaterial()->AddTextureElement(TextureElement("texture1", AssetLibrary::TileTexture));
	pr2->GetMaterial()->AddTextureElement(TextureElement("texture2", AssetLibrary::WallTexture));
	pr2->StencilValue = 16;
	pr2->StencilMask = StencilMaskBitfield::Bit_5;
	pr2->BindPreDraw(
		[](PrimitiveComponent* InComponent, Shader* InShader)
		{
			InShader->SetUniform1f("Specular", 0.8f);
		});

	pr3 = new PrimitiveComponent("PrimitiveComponent_3");
	pr3->SetStaticMesh(CubeMesh, 1, 1);
	pr3->GetMaterial()->SetShader(AssetLibrary::BaseShader);
	pr3->GetMaterial()->AddTextureElement(TextureElement("texture1", AssetLibrary::TileTexture));
	pr3->GetMaterial()->AddTextureElement(TextureElement("texture2", AssetLibrary::WallTexture));
	pr3->StencilValue = 16;
	pr3->StencilMask = StencilMaskBitfield::Bit_5;
	pr3->BindPreDraw(
		[](PrimitiveComponent* InComponent, Shader* InShader)
		{
			InShader->SetUniform1f("Specular", 0.8f);
		});
	pr3->SetRelativeLocation(Vector3f(-3.0f, 0.0f, 0.0f));


	LightSource_1 = new PointLightComponent("Point light 1");
	LightSource_1->SetAttenuation(1);
	LightSource_1->SetLightColor(LinearColor(1.0f, 0.0f, 0.0f, 1.0f));

	LightSource_2 = new PointLightComponent("Point light 2");
	LightSource_2->SetAttenuation(1);
	LightSource_2->SetLightColor(LinearColor(0.0f, 1.0f, 0.0f, 1.0f));

	LightSource_3 = new PointLightComponent("Point light 3");
	LightSource_3->SetAttenuation(1);
	LightSource_3->SetLightColor(LinearColor(0.0f, 0.0f, 1.0f, 1.0f));

	Actor1 = new Actor;
	Actor1->AttachSceneComponent(pr1);
	Actor1->AttachSceneComponent(pr2, pr1);
	Actor1->AttachSceneComponent(pr3, pr1);
	Actor1->AttachSceneComponent(LightSource_1);
	Actor1->AttachSceneComponent(LightSource_2);
	Actor1->AttachSceneComponent(LightSource_3);

	Actor1->SetActorScale(Vector3f(0.1f));

#if WITH_EDITOR
	Actor1->SetActorLabel("TestSphereActor");
#endif

	World::Get()->AddActor(Actor1);

	
	RockActor = new StaticMeshActor();
	RockActor->GetMeshComponent()->SetStaticMesh(AssetLibrary::RockMesh, 1, 1, 0, 1, 1);
	RockActor->GetMeshComponent()->GetMaterial()->SetShader(AssetLibrary::RockShader);
	RockActor->GetMeshComponent()->GetMaterial()->AddTextureElement(TextureElement("TextureAlbedo", AssetLibrary::Rock_Al_Texture));
	RockActor->GetMeshComponent()->GetMaterial()->AddTextureElement(TextureElement("TextureNormal", AssetLibrary::Rock_N_Texture));
	RockActor->GetMeshComponent()->GetMaterial()->AddTextureElement(TextureElement("TextureMasks", AssetLibrary::Rock_S_R_M_AO_Texture));
	RockActor->GetMeshComponent()->StencilValue = 16;
	RockActor->GetMeshComponent()->StencilMask = StencilMaskBitfield::Bit_5;

	RockActor->GetMeshComponent()->BindPreDraw(
		[](PrimitiveComponent* InComponent, Shader* InShader)
		{
			InShader->SetUniform2f("UVScale", Vector2f(1.0f));
		});

	RockActor->SetActorLocation(Vector3f(0.5f, 0.0f, -0.2f));
	RockActor->SetActorRotation(Rotatorf(0.0f, 00.0f, 180.0f));
	RockActor->SetActorScale(Vector3f(0.1f));

#if WITH_EDITOR
	RockActor->SetActorLabel("Rock");
#endif
	
	World::Get()->AddActor(RockActor);
	

	FloorActor = new StaticMeshActor();
	FloorActor->GetMeshComponent()->SetStaticMesh(AssetLibrary::PlaneMesh, 1, 1, 0, 1, 1);
	FloorActor->GetMeshComponent()->GetMaterial()->SetShader(AssetLibrary::RockShader);
	FloorActor->GetMeshComponent()->GetMaterial()->AddTextureElement(TextureElement("TextureAlbedo", AssetLibrary::WoodenFloor_Al_Texture));
	FloorActor->GetMeshComponent()->GetMaterial()->AddTextureElement(TextureElement("TextureNormal", AssetLibrary::WoodenFloor_N_Texture));
	FloorActor->GetMeshComponent()->GetMaterial()->AddTextureElement(TextureElement("TextureMasks", AssetLibrary::WoodenFloor_S_R_M_AO_Texture));
	FloorActor->GetMeshComponent()->StencilValue = 16;
	FloorActor->GetMeshComponent()->StencilMask = StencilMaskBitfield::Bit_5;

	FloorActor->GetMeshComponent()->BindPreDraw(
		[](PrimitiveComponent* InComponent, Shader* InShader)
		{
			InShader->SetUniform2f("UVScale", Vector2f(10.0f));
		});

	FloorActor->SetActorLocation(Vector3f(0.0f, 0.0f, -0.5f));
	FloorActor->SetActorRotation(Rotatorf(0.0f, 00.0f, 270.0f));
	FloorActor->SetActorScale(Vector3f(5.0f, 5.0f, 5.0f));

#if WITH_EDITOR
	FloorActor->SetActorLabel("Floor");
#endif

	World::Get()->AddActor(FloorActor);
	

	CameraActor* CameraAct = new CameraActor;

	CameraAct->GetCameraComponent()->SetFOV(45.0f);
	CameraAct->GetCameraComponent()->SetPerspectiveMinZ(0.25f);
	CameraAct->GetCameraComponent()->SetPerspectiveMaxZ(1000.0f);
	CameraAct->GetCameraComponent()->SetWorldLocation(Vector3f(-1, 0, .25));
	CameraAct->GetCameraComponent()->SetPerspectiveWidth(1920);
	CameraAct->GetCameraComponent()->SetPerspectiveHeight(1270);

#if WITH_EDITOR
	CameraAct->SetActorLabel("Camera");
#endif

	World::Get()->AddActor(CameraAct);

	CameraAct->GetCameraComponent()->Activate();

	GameSettings::Get()->SetWindowMode(EWindowMode::FullScreen);
	GameSettings::Get()->SetResolution(IntPoint(1440, 900));
	GameSettings::Get()->ApplySettings();
}

void GameApplication::Tick(float DeltaTime)
{
	Application::Tick(DeltaTime);

	Actor1->SetActorLocation(Vector3f(/*Math::Cos(Renderer::GetTime())*/ 1, 0, 0));

	pr1->SetRelativeLocation(Vector3f(1.0, 0, 0));

	pr2->SetRelativeLocation(Vector3f(Math::Sin(Renderer::GetTime()), Math::Cos(Renderer::GetTime()), 0.0f));
	pr2->SetRelativeRotation(Rotatorf(0.0f, Math::Cos(Renderer::GetTime()) * 360.0f, 0.0f));

	LightSource_1->SetRelativeLocation(Vector3f(Math::Sin(Renderer::GetTime()), Math::Cos(Renderer::GetTime()), 0.0f));

	LightSource_2->SetRelativeLocation(Vector3f(Math::Sin(Renderer::GetTime()), 0, 0.0f));

	LightSource_3->SetRelativeLocation(Vector3f(Math::Cos(Renderer::GetTime()), 0, 0.0f));
}