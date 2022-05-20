#include "DurnaPCH.h"
#include "Renderer.h"

#include "Runtime/Window/Window.h"
#include "Runtime/Engine/Camera/CameraManager.h"
#include "Runtime/Renderer/ImGui/ImGuiRenderer.h"
#include "Runtime/Renderer/ImGui/ImGuiLayer.h"

//#include <imgui.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Runtime/Assets/AssetLibrary.h"
#include "Runtime/Engine/BaseShapes.h"

#include "runtime/Engine/GameFramwork/StaticMeshActor.h"
#include "Runtime/renderer/RenderCommands.h"
#include "runtime/Components/PrimitiveComponent.h"
#include "Runtime/Renderer/Shader.h"
#include "Runtime/Renderer/Material.h"

#include "Runtime/Math/LinearColor.h"

#include "Runtime/renderer/FrameBuffer.h"
#include "Runtime/Renderer/RenderQueue.h"

#include "Runtime/Renderer/Buffer.h"
#include "Runtime/Engine/Camera/CameraComponent.h"

LOG_DEFINE_CATEGORY(LogRenderer, "Renderer")

namespace Durna
{
	std::unique_ptr<Window> Renderer::MainWindow = nullptr;
	float Renderer::Time = 0.0f;

	std::shared_ptr<FrameBuffer> Renderer::GBuffer = nullptr;

	RenderQueue Renderer::RenderQue;

	Material Renderer::PostProccessMaterial;
	PostProcessSetting Renderer::PPSetting;

	uint32 Renderer::framebuffer;
	uint32 Renderer::textureColorbuffer;
	uint32 Renderer::textureDepth;
	uint32 Renderer::textured;
	uint32 Renderer::textures;

	void Renderer::UpdatePostProcessUniforms()
	{
		if (PostProccessMaterial.GetShader())
		{
			PostProccessMaterial.Use();
			
			// Fog
			PostProccessMaterial.GetShader()->SetUniformVec3f("FogColor", PPSetting.FogColor);
			PostProccessMaterial.GetShader()->SetUniform1f("FogAmount", PPSetting.FogAmount);
			PostProccessMaterial.GetShader()->SetUniform1f("FogOffset", PPSetting.FogOffset);
			PostProccessMaterial.GetShader()->SetUniform1f("FogLength", PPSetting.FogLength);

			//Blur
			PostProccessMaterial.GetShader()->SetUniform1f("BlurStepSize", PPSetting.BlurStepSize);
			PostProccessMaterial.GetShader()->SetUniform1i("BlurStepNumber", PPSetting.BlurStepNumber);
		}
	}

	Renderer::Renderer()
	{ }

	Renderer::~Renderer()
	{ }

	void Renderer::Init()
	{
		LOG(LogRenderer, Info, "Initializing.");

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		MainWindow = std::make_unique <Window>("DurnaEngine", 800, 600);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG(LogRenderer, Error, "Failed to initialize GLAD");
			return;
		}

		ImGuiRenderer::Get()->Init();

		AssetLibrary::Init();

		RenderCommands::SetClearColor(LinearColor(0.2f, 0.2f, 0.3f, 1.0f));
		RenderCommands::EnableBackFaceCulling();

// 		GBuffer = FrameBuffer::Create();
// 		GBuffer->Bind();
// 		
// 		GBuffer->AddAttachment("Buffer_Color", FrameBufferAttachmentType::Color_0,
// 			FrameBufferAttachmentFormat::RGBA, FrameBufferAttachmentFormat::RGBA,
// 			FrameBufferAttachmentDataType::uByte);

// 		GBuffer->AddAttachment("Buffer_Depth", FrameBufferAttachmentType::Depth_Stencil,
// 			FrameBufferAttachmentFormat::Depth_Stencil, FrameBufferAttachmentFormat::Depth24_Stencil8,
// 			FrameBufferAttachmentDataType::uInt_24_8);

// 		GBuffer->SetDepthStencilAttachment("Buffer_Depth", "Buffer_Stencil", FrameBufferAttachmentType::Depth_Stencil, 
// 			FrameBufferAttachmentFormat::Depth_Stencil, FrameBufferAttachmentFormat::Depth24_Stencil8,
// 			FrameBufferAttachmentDataType::uInt_24_8);
// 
// 
// 		GBuffer->SetSize(800, 600);

		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		glGenTextures(1, &textureColorbuffer);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);


// 		glGenTextures(1, &textured);
// 		glBindTexture(GL_TEXTURE_2D, textured);
// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, 800, 600, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 		glBindTexture(GL_TEXTURE_2D, 0);
// 
// 		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, textured, 0);
// 
// 
// 		glGenTextures(1, &textures);
// 		glBindTexture(GL_TEXTURE_2D, textures);
// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_INDEX8, 800, 600, 0, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, NULL);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 		glBindTexture(GL_TEXTURE_2D, 0);
// 
// 		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, textures, 0);



// 		glGenTextures(1, &textureDepth);
// 		glBindTexture(GL_TEXTURE_2D, textureDepth);
// 		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, 800, 600);
// 
// 		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, textureDepth, 0);
// 
// 		glGenTextures(1, &textured);
// 		glTextureView(textured, GL_TEXTURE_2D, textureDepth,
// 			GL_DEPTH24_STENCIL8, 0, 1, 0, 1);
// 		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_DEPTH_COMPONENT);
// 
// 		glGenTextures(1, &textures);
// 		glTextureView(textures, GL_TEXTURE_2D, textureDepth,
// 			GL_DEPTH24_STENCIL8, 0, 1, 0, 1);
// 		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_STENCIL_INDEX);


		glGenTextures(1, &textureDepth);
		glBindTexture(GL_TEXTURE_2D, textureDepth);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, 800, 600);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, textureDepth, 0);

		
		glGenTextures(1, &textures);
		glTextureView(textures, GL_TEXTURE_2D, textureDepth,
			GL_DEPTH24_STENCIL8, 0, 1, 0, 1);
		glBindTexture(GL_TEXTURE_2D, textures);
		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_STENCIL_INDEX);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		glGenTextures(1, &textured);
		glTextureView(textured, GL_TEXTURE_2D, textureDepth,
			GL_DEPTH24_STENCIL8, 0, 1, 0, 1);
		glBindTexture(GL_TEXTURE_2D, textured);
		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_DEPTH_COMPONENT);





		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_UNSUPPORTED)
			std::cout << "wwwwwwwwwwwwwwwwwwwww!" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		PostProccessMaterial.SetShader(AssetLibrary::PostProcessShader);

		//RenderCommands::SetDrawWireframe();
	}

	void Renderer::Tick(float DeltaTime)
	{
		MainWindow->Tick(DeltaTime);
		Time += DeltaTime;

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		//GBuffer->Bind();
		RenderCommands::ClearColorBuffer();
		RenderCommands::ClearDepthBuffer();
		RenderCommands::EnableDepthTest();
		
		glEnable(GL_STENCIL_TEST);
		glStencilMask(0xFF);
		glClear(GL_STENCIL_BUFFER_BIT);

		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		for (PrimitiveComponent* Pr : RenderQue.Queue)
		{
			if (Pr)
			{
				RenderCommands::DrawPrimitive(Pr);
			}
		}

		//GBuffer->Unbind();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		RenderCommands::ClearColorBuffer();
		RenderCommands::DisableDepthTest();
		RenderCommands::DisableStencilTest();


		PostProccessMaterial.GetShader()->Use();
		
		Texture::ActivateTexture(0);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		int UniformLocation = glGetUniformLocation(PostProccessMaterial.GetShader()->ID, "Buffer_Color");
		glUniform1i(UniformLocation, 0);


		Texture::ActivateTexture(1);
		glBindTexture(GL_TEXTURE_2D, textured);
		UniformLocation = glGetUniformLocation(PostProccessMaterial.GetShader()->ID, "Buffer_Depth");
		glUniform1i(UniformLocation, 1);


		Texture::ActivateTexture(2);
		glBindTexture(GL_TEXTURE_2D, textures);
		UniformLocation = glGetUniformLocation(PostProccessMaterial.GetShader()->ID, "Buffer_Stencil");
		glUniform1i(UniformLocation, 2);


		AssetLibrary::ScreenQuad->VA->Bind();

		glDrawElements(GL_TRIANGLES, AssetLibrary::ScreenQuad->EB->GetCount(), GL_UNSIGNED_INT, 0);


#if WITH_EDITOR
		UpdatePostProcessUniforms();
#endif

// 		GBuffer->BindTextures(PostProccessMaterial.GetShader()->ID);
// 		RenderCommands::DrawFrameBufferToScreen(GBuffer.get(), &PostProccessMaterial);

#if WITH_EDITOR
		ImGuiRenderer::Get()->Tick(DeltaTime);
#endif

		glfwPollEvents();
		glfwSwapBuffers(MainWindow->GetGLFWWindow());

		RenderQue.Clear();
	}

	void Renderer::Shutdown()
	{
		LOG(LogRenderer, Info, "Shutingdown");
		glfwTerminate();
	}

	Window* Renderer::GetWindow()
	{
		return MainWindow.get();
	}

	float Renderer::GetTime()
	{
		return Time;
	}

	void Renderer::OnResizeWindow(int32 InWidth, int32 InHeight)
	{
		if (GBuffer.get())
		{
			GBuffer->SetSize(InWidth, InHeight);
		}

		if (CameraComponent* CameraComp = CameraManager::Get()->GetActiveCamera())
		{
			CameraComp->SetPerspectiveWidth(InWidth);
			CameraComp->SetPerspectiveHeight(InHeight);
			CameraManager::Get()->MarkDirtyProjection();
		}
	}

	void Renderer::RegisterToRenderQueue(PrimitiveComponent* Pr)
	{
		RenderQue.AddPrimitive(Pr);
	}

}