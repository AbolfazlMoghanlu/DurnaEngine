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
#include "Runtime/Engine/Image/Image.h"

#include "ThirdParty/Stb/stb_image.h"

LOG_DEFINE_CATEGORY(LogRenderer, "Renderer")

namespace Durna
{
	Window* Renderer::MainWindow = nullptr;

	Shader* Renderer::shader;

	PrimitiveComponent* Renderer::pr;

	Durna::Image* Renderer::img;

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

 		shader = new Shader(Path::ShaderRelativePath("BaseShader.glsl"));
 		shader->Use();

		pr = new PrimitiveComponent(&BaseShapes::Cube, shader);

		img = new Image(Path::TextureRelativePath("T_TiledTexureCoordiante.png").c_str());
	}

	void Renderer::Tick(float DeltaTime)
	{
		MainWindow->Tick(DeltaTime);

		glEnable(GL_DEPTH_TEST);

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDepthFunc(GL_LESS);

// 		glEnable(GL_CULL_FACE);
// 		glCullFace(GL_BACK);
// 		glFrontFace(GL_CW);

//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		shader->SetUniformVec3f("CameraPosition", CameraManager::GetActiveCameraPosition());

		float M[16];
		CameraManager::GetCameraViewMatrix(M);

		int l = glGetUniformLocation(shader->ID, "view");

		glUniformMatrix4fv(l, 1, false, M);



		unsigned int texture;
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->GetWidth(), img->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, img->Data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);



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