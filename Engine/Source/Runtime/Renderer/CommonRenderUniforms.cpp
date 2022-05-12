#include "DurnaPCH.h"
#include "CommonRenderUniforms.h"

#include "Runtime/Renderer/Shader.h"
#include "Runtime/Renderer/Renderer.h"
#include "Runtime/Engine/Camera/CameraManager.h"

namespace Durna
{
	void CommonRenderUniforms::UploadRenderTime(Shader* InShader)
	{
		InShader->SetUniform1f("Time", Renderer::GetTime());
	}

	void CommonRenderUniforms::UploadCameraLocation(Shader* InShader)
	{
		InShader->SetUniformVec3f("CameraLocation", CameraManager::Get()->GetViewLocation());
	}
}