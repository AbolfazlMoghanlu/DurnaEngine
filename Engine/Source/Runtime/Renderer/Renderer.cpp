#include "DurnaPCH.h"
#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Runtime/Window/Window.h"

//todo remove dependancy
#include "Runtime/Renderer/Buffer.h"

//TODO: make proper shader class
const char *vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 VColor;\n"
"out vec4 V_Color;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	V_Color = VColor;\n"
"}\n";

const char* fragmentshadersource = "#version 460 core\n"
"out vec4 FragColor;\n"
"in vec4 V_Color;\n"
"void main()\n"
"{\n"
"	FragColor = V_Color;\n"
"}\n";


namespace Durna
{
	Window* Renderer::MainWindow = nullptr;

	void Renderer::Init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		MainWindow = new Window("DurnaEngine", 800, 600);
		MainWindow->Init();

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
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

		
		unsigned int vertexshader;
		vertexshader = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertexshader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexshader);

		int  success;
		char infoLog[512];
		glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertexshader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}


		unsigned int fragmentshader;
		fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(fragmentshader, 1, &fragmentshadersource, nullptr);
		glCompileShader(fragmentshader);

		glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(fragmentshader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED\n" << infoLog << std::endl;
		}


		unsigned int shaderprogram;
		shaderprogram = glCreateProgram();

		glAttachShader(shaderprogram, vertexshader);
		glAttachShader(shaderprogram, fragmentshader);
		glLinkProgram(shaderprogram);

		glGetProgramiv(shaderprogram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderprogram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		glUseProgram(shaderprogram);

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
		delete MainWindow;

		glfwTerminate();
	}

}