#include "DurnaPCH.h"
#include "Renderer.h"

#include "Runtime/Window/Window.h"
#include "Runtime/Renderer/Shader.h"
#include "Runtime/Engine/Camera/CameraManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//todo remove dependancy
#include "Runtime/Renderer/Buffer.h"
#include "Runtime/Engine/BaseShapes.h"
#include "Runtime/Components/PrimitiveComponent.h"
#include "Runtime/Renderer/RenderCommands.h"

LOG_DEFINE_CATEGORY(LogRenderer, "Renderer")

namespace Durna
{
	Window* Renderer::MainWindow = nullptr;

	Shader* Renderer::shader;

	PrimitiveComponent* Renderer::pr;

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

		std::vector<float> vc =
		{
			1.0		, 0.0		, 0.0		, 1.0,
			0.0		, 1.0		, 0.0		, 1.0,
			0.0		, 0.0		, 1.0		, 1.0,
			1.0		, 1.0		, 1.0		, 1.0
		};

 		shader = new Shader(Path::ShaderRelativePath("BaseShader.glsl"));
 		shader->Use();

		pr = new PrimitiveComponent(&BaseShapes::Plane, shader);
		pr->UpdateVertexColor(vc);

		/*
		std::vector<float> vc = 
		{	
			1.0		, 0.0		, 0.0		, 1.0,
			0.0		, 1.0		, 0.0		, 1.0,
			0.0		, 0.0		, 1.0		, 1.0,
			1.0		, 1.0		, 1.0		, 1.0 
		};

		Shader shader(Path::ShaderRelativePath("BaseShader.glsl"));
		shader.Use();

		PrimitiveComponent* c;
		pr->UpdateVertexColor(vc);

		shader.SetUniformVec3f("CameraPosition", Vector3f(0.5, 0, 0));

		RenderCommands::DrawPrimitive(*pr);
		*/
	}

	void Renderer::Tick(float DeltaTime)
	{
		MainWindow->Tick(DeltaTime);

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->SetUniformVec3f("CameraPosition", CameraManager::GetCameraPosition());
		RenderCommands::DrawPrimitive(*pr);

		glfwPollEvents();
	}

	void Renderer::Shutdown()
	{
		delete MainWindow;
		LOG(LogRenderer, Info, "Shutingdown");

		glfwTerminate();
	}

}