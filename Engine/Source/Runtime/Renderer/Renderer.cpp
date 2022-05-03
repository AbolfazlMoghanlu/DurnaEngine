#include "DurnaPCH.h"
#include "Renderer.h"

#include "Runtime/Window/Window.h"
#include "Runtime/Engine/Camera/CameraManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Runtime/Assets/AssetLibrary.h"


LOG_DEFINE_CATEGORY(LogRenderer, "Renderer")

namespace Durna
{
	Window* Renderer::MainWindow = nullptr;
	float Renderer::Time = 0.0f;

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
		
	}

	void Renderer::Tick(float DeltaTime)
	{
		MainWindow->Tick(DeltaTime);
		CameraManager::Tick(DeltaTime);

		glEnable(GL_DEPTH_TEST);

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDepthFunc(GL_LESS);
		glDepthRange(0, 100);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		Time += DeltaTime;

		glfwPollEvents();
	}

	void Renderer::Shutdown()
	{
		delete MainWindow;
		LOG(LogRenderer, Info, "Shutingdown");

		glfwTerminate();
	}

	Window* Renderer::GetWindow()
	{
		return MainWindow;
	}

	float Renderer::GetTime()
	{
		return Time;
	}

}