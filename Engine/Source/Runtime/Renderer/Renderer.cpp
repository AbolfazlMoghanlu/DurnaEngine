#include "DurnaPCH.h"
#include "Renderer.h"

#include "Runtime/Window/Window.h"
#include "Runtime/Renderer/Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//todo remove dependancy
#include "Runtime/Renderer/Buffer.h"

LOG_DEFINE_CATEGORY(LogRenderer, "Renderer")

namespace Durna
{
	Window* Renderer::MainWindow = nullptr;

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
		MainWindow->Init();

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG(LogRenderer, Error, "Failed to initialize GLAD");
			return;
		}

		///////////////////////////////////////////////////////////////

		unsigned int vertexarrayobject;
		glGenVertexArrays(1, &vertexarrayobject);
		glBindVertexArray(vertexarrayobject);

		std::vector<float> vp = 
		{	
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left
		};

		std::vector<float> vc = 
		{	
			1.0		, 0.0		, 0.0		, 1.0,
			0.0		, 1.0		, 0.0		, 1.0,
			0.0		, 0.0		, 1.0		, 1.0,
			1.0		, 1.0		, 1.0		, 1.0
		};

		unsigned int indices[] =
		{
			0, 1, 3,
			1, 2, 3
		};
		
		VertexBuffer vb = VertexBuffer(vp, vc);

		Shader shader(Path::ShaderRelativePath("BaseShader.glsl"));
		shader.Use();


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);


		unsigned int elementbufferobject;
		glGenBuffers(1, &elementbufferobject);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbufferobject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	}

	void Renderer::Tick(float DeltaTime)
	{
		MainWindow->Tick(DeltaTime);

		//glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();
	}

	void Renderer::Shutdown()
	{
		LOG(LogRenderer, Info, "Shutingdown");
		delete MainWindow;

		glfwTerminate();
	}

}