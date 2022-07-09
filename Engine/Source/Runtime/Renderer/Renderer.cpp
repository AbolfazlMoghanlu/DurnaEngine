#include "DurnaPCH.h"
#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Runtime/Window/Window.h"
#include "Runtime/Engine/Camera/CameraManager.h"
#include "Runtime/Renderer/ImGui/ImGuiRenderer.h"

#include "Runtime/Assets/AssetLibrary.h"
#include "Runtime/Engine/BaseShapes.h"

#include "Runtime/renderer/RenderCommands.h"
#include "runtime/Components/PrimitiveComponent.h"
#include "Runtime/Renderer/Shader.h"
#include "Runtime/Renderer/Material.h"

#include "Runtime/renderer/FrameBuffer/FrameBuffer.h"
#include "Runtime/Renderer/RenderQueue.h"

#include "Runtime/Renderer/FrameBuffer/GBuffer.h"
#include "Runtime/Renderer/FrameBuffer/ResolveDefferedBuffer.h"
#include "Runtime/Renderer/FrameBuffer/ShadowFrameBuffer.h"

#include "Runtime/Engine/GameFramwork/GameSettings.h"
#include "Runtime/Math/ViewMatrix.h"
#include "Runtime/Math/OrthoMatrix.h"

#include "Runtime/Engine/GameFramwork/DirectionalLightActor.h"
#include "Runtime/Components/DirectionalLightComponent.h"
#include "Runtime/Engine/GameFramwork/SkyLightActor.h"
#include "Runtime/Components/SkyLightComponent.h"
#include "Runtime/Engine/GameFramwork/SkySphereActor.h"
#include "Runtime/Components/SkySphereComponent.h"
#include "Runtime/Engine/World.h"

#include "Runtime/Renderer/Buffer.h"
#include "Runtime/Math/ScaleRotationTranslationMatrix.h"
#include "Runtime/Math/PrespectiveMatrix.h"
#include "Runtime/Renderer/CommonRenderUniforms.h"

#include "Runtime/Components/Light/PointLightComponent.h"

#if WITH_EDITOR
	#include "Editor/Settings/Settings.h"
#endif


LOG_DEFINE_CATEGORY(LogRenderer, "Renderer")

namespace Durna
{
	std::shared_ptr<Window> Renderer::MainWindow = nullptr;
	float Renderer::Time = 0.0f;

	std::shared_ptr<GBuffer> Renderer::Gbuffer = nullptr;

	RenderQueue Renderer::RenderQue;
	PointLightRenderQueue Renderer::PointLightRenderQue;

	Material Renderer::PostProccessMaterial;
	Material Renderer::ResolvedMaterial;

	PostProcessSetting Renderer::PPSetting;

	void Renderer::UpdatePostProcessUniforms()
	{
		if (PostProccessMaterial.GetShader())
		{
			PostProccessMaterial.Use();
			
#if WITH_EDITOR

			// Display buffer
			PostProccessMaterial.GetShader()->SetUniform1i("DisplayBufer",
				static_cast<int32>(Settings::Get()->GetDisplayBuffer()));
#endif

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

		MainWindow = Window::Create("DurnaEngine", 800, 600);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG(LogRenderer, Error, "Failed to initialize GLAD");
			return;
		}

		ImGuiRenderer::Get()->Init();

		AssetLibrary::Init();

		RenderCommands::SetClearColor(LinearColor(0.2f, 0.2f, 0.3f, 1.0f));
		RenderCommands::EnableBackFaceCulling();

		RenderCommands::SetStencilOperationReplace();

		Gbuffer = GBuffer::Create();

		PostProccessMaterial.SetShader(AssetLibrary::PostProcessShader);
		UpdatePostProcessUniforms();

		ResolvedMaterial.SetShader(AssetLibrary::ResolvedShader);
	}

	void Renderer::Tick(float DeltaTime)
	{
		MainWindow->Tick(DeltaTime);
		Time += DeltaTime;

		Render();

#if !WITH_EDITOR
		RenderCommands::SetViewportSize(MainWindow->ConstraintedResolution, MainWindow->ConstraintedOffset);
		
		// if editor is present, we draw resolved buffer to viewport so there is no need to draw resolved buffer to glfw window
		RenderCommands::DrawFrameBufferToScreen(Gbuffer.get(), &ResolvedMaterial);
#endif


#if WITH_EDITOR
		ImGuiRenderer::Get()->Tick(DeltaTime);
#endif

		glfwPollEvents();
		glfwSwapBuffers(MainWindow->GetGLFWWindow());

		RenderQue.Clear();
		PointLightRenderQue.Clear();
	}


	void Renderer::Render()
	{
		RenderShadowBuffers();

		BeginRenderGBuffer();
		RenderGBuffer();
		FinishRenderGBuffer();

		RenderSceneLights();

		ResolveFinalColor();

		ResolvePostproccess();
	}


	void Renderer::BeginRenderGBuffer()
	{
		Gbuffer->Bind();
		Gbuffer->BindDrawBuffers();

		RenderCommands::ClearColorBuffer();

		RenderCommands::EnableDepthTest();
		RenderCommands::ClearDepthBuffer();

		RenderCommands::EnableStencilTest();
		RenderCommands::ClearStencilBuffer();

		RenderCommands::SetViewportSize(MainWindow->Resolution);
	}

	void Renderer::RenderGBuffer()
	{
		for (PrimitiveComponent* Pr : RenderQue.Queue)
		{
			if (Pr)
			{
				RenderCommands::DrawPrimitive(Pr);
			}
		}
	}

	void Renderer::FinishRenderGBuffer()
	{
		//Gbuffer->Unbind();
		//Gbuffer->UnbindDrawBuffers();
	}

	void Renderer::RenderShadowBuffers()
	{
		glEnable(GL_DEPTH_TEST);


		DirectionalLightComponent* DirectionalLightSource = World::Get()->GetDirectionalLight()->GetLightComponent();
		
		if (DirectionalLightSource && DirectionalLightSource->IsVisible() && DirectionalLightSource->GetCastShadow())
		{
			std::shared_ptr<ShadowFrameBuffer> DirectionalLightFBO = DirectionalLightSource->GetShadowFrameBuffer();

			if (DirectionalLightFBO.get())
			{
				RenderCommands::SetViewportSize(DirectionalLightSource->GetShadowResolution());
				DirectionalLightFBO->Bind();

				glClear(GL_DEPTH_BUFFER_BIT);

				for (PrimitiveComponent* Pr : RenderQue.Queue)
				{
					if (Pr && Pr->GetCastShadow())
					{
						RenderCommands::DrawPrimitive(Pr, DirectionalLightSource->GetViewMatrix(),
							DirectionalLightSource->GetProjectionMatrix());
					}
				}
			}

		}

	}

	void Renderer::RenderSceneLights()
	{
		RenderCommands::DisableDepthTest();
		RenderCommands::DisableStencilTest();

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);

		Gbuffer->BindDrawBuffers();

		uint32 LightTextureID = Gbuffer->Attachments[5]->TextureID;
		static const float Black[] = { 0, 0, 0, 0 };
		glClearTexImage(LightTextureID, 0, GL_RGBA, GL_UNSIGNED_BYTE, Black);

		Shader* PointLightShader = AssetLibrary::PointLightShader;
		PrimitiveComponent* Pr = AssetLibrary::PointLightSphere;

		Pr->VA->Bind();
		PointLightShader->Use();

		Gbuffer->BindTextures(PointLightShader->ID);
		CommonRenderUniforms::UploadCameraLocation(PointLightShader);

		PointLightShader->SetUniformMatrix4f("View", CameraManager::Get()->GetCameraViewMatrix());
		PointLightShader->SetUniformMatrix4f("Projection", CameraManager::Get()->GetProjectionMatrix());

		for (PointLightComponent* Light : PointLightRenderQue.Queue)
		{
			Vector3f LightLocation = Light->GetWorldLocation();
			float LightAttenuation = Light->GetAttenuation();
			LinearColor LightColor = Light->GetLightColor() * Light->GetIntensity();

			PointLightShader->SetUniformVec3f("LightLocation", LightLocation);
			PointLightShader->SetUniform1f("Attenuation", LightAttenuation);
			PointLightShader->SetUniformVec3f("LightColor", LightColor);

			ScaleRotationTranslationMatrix<float> Transform(Vector3f(LightAttenuation), Rotatorf(0.0f), LightLocation);
			PointLightShader->SetUniformMatrix4f("Transform", Transform.M[0]);

			glDrawElements(GL_TRIANGLES, Pr->EB->GetCount(), GL_UNSIGNED_INT, 0);
		}

		glDisable(GL_BLEND);
	}

	void Renderer::ResolveFinalColor()
	{
		RenderCommands::DisableDepthTest();
		RenderCommands::DisableStencilTest();

		Shader* BasepassShader = AssetLibrary::BasepassShader;
		BasepassShader->Use();

		// Light
		BasepassShader->SetUniform1f("AmbientLightIntensity", World::Get()->GetSkyLight() ?
			World::Get()->GetSkyLight()->GetLightComponent()->GetIntensity() : 1.0f);

		BasepassShader->SetUniformVec3f("AmbientLightColor", World::Get()->GetSkyLight() ?
			World::Get()->GetSkyLight()->GetLightComponent()->GetLightColor() : LinearColor::White);

		BasepassShader->SetUniformVec3f("DiffuseLightColor", World::Get()->GetDirectionalLight() ?
			World::Get()->GetDirectionalLight()->GetLightComponent()->GetLightColor() : LinearColor::White);

		BasepassShader->SetUniform1f("DiffuseLightIntensity", World::Get()->GetDirectionalLight() ?
			World::Get()->GetDirectionalLight()->GetLightComponent()->GetIntensity() : 1.0f);

		Rotatorf DiffuseLightRotation = World::Get()->GetDirectionalLight() ?
			World::Get()->GetDirectionalLight()->GetLightComponent()->GetWorldRotation() : Rotatorf(0.0f);

		BasepassShader->SetUniformVec3f("DiffuseLightDirection", DiffuseLightRotation.GetForwardVector());

		DirectionalLightComponent* DirectionalLightSource = World::Get()->GetDirectionalLight()->GetLightComponent();
		if (DirectionalLightSource && DirectionalLightSource->IsVisible() && DirectionalLightSource->GetCastShadow())
		{
			std::shared_ptr<ShadowFrameBuffer> DirectionalLightFBO = DirectionalLightSource->GetShadowFrameBuffer();

			if (DirectionalLightFBO.get())
			{
				BasepassShader->Use();
				Texture::ActivateTexture(10);

				glBindTexture(GL_TEXTURE_2D, DirectionalLightFBO->GetTextureID());

				int UniformLocation = glGetUniformLocation(BasepassShader->ID, "ShadowMap");
				glUniform1i(UniformLocation, 10);

				Matrix<float> V = DirectionalLightSource->GetViewMatrix();
				Matrix<float> P = DirectionalLightSource->GetProjectionMatrix();

				BasepassShader->SetUniformMatrix4f("LightMatrix", V.M[0]);
				BasepassShader->SetUniformMatrix4f("Projection", P.M[0]);

				BasepassShader->SetUniformVec3f("LightLocation", DirectionalLightSource->GetWorldLocation());
				Rotatorf DirectionalLightRotation = DirectionalLightSource->GetWorldRotation();
				BasepassShader->SetUniformVec3f("LightDirection", DirectionalLightRotation.GetForwardVector());
			}
		}


		SkySphereActor* SkySphere = World::Get()->GetSkySphere();
		Texture* EnvironmentCubemap = SkySphere->GetSkyComponent()->GetCubemap();

		if (EnvironmentCubemap)
		{
			Texture::ActivateTexture(11);
			EnvironmentCubemap->Bind();

			int UniformLocation = glGetUniformLocation(BasepassShader->ID, "EnvironmentCubemap");
			glUniform1i(UniformLocation, 11);
		}

		RenderCommands::DrawFrameBufferToScreen(Gbuffer.get(), BasepassShader);

// #if !WITH_EDITOR
// 		RenderCommands::SetViewportSize(MainWindow->ConstraintedResolution, MainWindow->ConstraintedOffset);
// #endif
	}

	void Renderer::ResolvePostproccess()
	{	
		PostProccessMaterial.GetShader()->Use();
#if WITH_EDITOR
		// if there is editor keep uniforms in update with parameters in ui
		UpdatePostProcessUniforms();
#endif

		RenderCommands::DrawFrameBufferToScreen(Gbuffer.get(), &PostProccessMaterial);

		Gbuffer->Unbind();
		Gbuffer->UnbindDrawBuffers();
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

	void Renderer::OnResolutionChanged(const IntPoint& InResolution)
	{
		ResizeBuffers(InResolution);
	}

	void Renderer::ResizeBuffers(const IntPoint& InResolution)
	{
		if (Gbuffer.get())
		{
			Gbuffer->SetSize(InResolution.X, InResolution.Y);
		}
	}

	void Renderer::RegisterToRenderQueue(PrimitiveComponent* Pr)
	{
		RenderQue.AddPrimitive(Pr);
	}

	void Renderer::RegisterPointLight(PointLightComponent* InPointLightComponent)
	{
		PointLightRenderQue.AddPrimitive(InPointLightComponent);
	}

}