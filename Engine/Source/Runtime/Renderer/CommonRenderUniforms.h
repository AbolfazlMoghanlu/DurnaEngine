#pragma once

namespace Durna
{
	class Shader;
	class PrimitiveComponent;

	class CommonRenderUniforms
	{
	public:
		static void UploadRenderTime(Shader* InShader);
		static void UploadCameraLocation(Shader* InShader);
		static void UploadCameraForwardVector(Shader* InShader);

		static void UploadOrientation(Shader* InShader, PrimitiveComponent* Pr);
	};
}

