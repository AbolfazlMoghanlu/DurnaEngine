#include "DurnaPCH.h"
#include "Renderer.h"

#include "Runtime/Window/Window.h"
#include "Runtime/Renderer/Shader.h"
#include "Runtime/Engine/Camera/CameraManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//todo remove dependency
#include "Runtime/Math/Math.h"
#include "Runtime/Engine/BaseShapes.h"
#include "Runtime/Components/PrimitiveComponent.h"
#include "Runtime/Renderer/RenderCommands.h"
#include "Runtime/Renderer/Material.h"
#include "Runtime/Math/TranslationMatrix.h"
#include "Runtime/Engine/Actor.h"

#include "Runtime/Assets/AssetLibrary.h"


LOG_DEFINE_CATEGORY(LogRenderer, "Renderer")

namespace Durna
{
	Window* Renderer::MainWindow = nullptr;

	// TODO: Remove
	PrimitiveComponent* Renderer::pr;

	PrimitiveComponent* Renderer::pr1;

	float Renderer::Time = 0.0f;

	Vector3f Renderer::PrLocation = Vector3f(0);

	Actor* Renderer::Actor1;

	Renderer::Renderer()
	{

	}

	void Renderer::Init()
	{
		LOG(LogRenderer, Info, "Initializing.");

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		MainWindow = new Window("DurnaEngine", 800, 600);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG(LogRenderer, Error, "Failed to initialize GLAD");
			return;
		}

		///////////////////////////////////////////////////////////////

		unsigned int vertexarrayobject;
		glGenVertexArrays(1, &vertexarrayobject);
		glBindVertexArray(vertexarrayobject);

		AssetLibrary::Init();
		
		pr = new PrimitiveComponent(&BaseShapes::Cube, AssetLibrary::BaseMaterial);
//		pr1 = new PrimitiveComponent(&BaseShapes::Cube, AssetLibrary::BaseMaterial);

		Actor1 = new Actor();
		Actor1->AttachSceneComponent(pr, Actor1->GetRoot());
//		Actor1->AttachSceneComponent(pr1, pr);
		
	}

	void Renderer::Tick(float DeltaTime)
	{
		MainWindow->Tick(DeltaTime);

		glEnable(GL_DEPTH_TEST);

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDepthFunc(GL_LESS);
		glDepthRange(0, 100);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		/*
		pr->SourceMaterial->GetShader()->Use();

		pr->SourceMaterial->GetShader()->SetUniformVec3f("CameraPosition", CameraManager::GetActiveCameraPosition());

		float M[16];
		CameraManager::GetCameraViewMatrix(M);

		int l = glGetUniformLocation(pr->SourceMaterial->GetShader()->ID, "view");
		glUniformMatrix4fv(l, 1, false, M);
		*/
		
		Time += DeltaTime;

		CameraManager::GetActiveCamera()->SetFOV(Math::Sin(Time) * 60);

		Actor1->SetActorLocation(Vector3f(0, 0, 2));
		Actor1->SetActorRotation(Rotatorf(Math::Sin(Time) * 360, Math::Cos(Time) * 360, Math::Cos(Math::Sin(Time)) * 360));
		
		//Actor1->SetActorLocation(Vector3f(Math::Sin(Time), 0, 3));
		//pr1->SetRelativeLocation(Vector3f(0, Math::Cos(Time), 0), false);

// 		const Rotatorf Rot = Rotatorf::CombineRotators(Actor1->GetActorRotation(), Rotatorf(Math::Sin(Time), Math::Cos(Time), Time));
// 		Actor1->SetActorRotation(Rot);
// 
// 		Actor1->SetActorScale(Vector3f(Math::Sin(Time), Math::Sin(Time), Math::Sin(Time)));
// 		pr1->SetRelativeScale(Vector3f(1, Math::Cos(Time), 1), false);

		Actor1->Tick(DeltaTime);

		glfwPollEvents();
	}

	void Renderer::Shutdown()
	{
		delete MainWindow;
		LOG(LogRenderer, Info, "Shutingdown");

		glfwTerminate();
	}

}