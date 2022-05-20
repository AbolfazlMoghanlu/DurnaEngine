#pragma once

#include "Runtime/Renderer/FrameBuffer.h"

namespace Durna
{
	class GBuffer : public FrameBuffer
	{
	public:
		GBuffer();
		virtual ~GBuffer();

		static std::shared_ptr<GBuffer> Create();

		virtual void BindTextures(uint32 ShaderID) override;
		virtual void RebuildBuffer() override;

	protected:
		uint32 DepthStencilTextureID;
		uint32 DepthTextureID;
		uint32 StencilTextureID;

	private:
		friend class RenderCommands;
	};
}