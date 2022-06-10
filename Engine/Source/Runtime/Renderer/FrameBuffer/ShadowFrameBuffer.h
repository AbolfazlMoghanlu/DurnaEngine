#pragma once

#include "Runtime/Renderer/FrameBuffer/FrameBuffer.h"

namespace Durna
{
	class ShadowFrameBuffer : public FrameBuffer
	{
	public:
		ShadowFrameBuffer();
		virtual ~ShadowFrameBuffer();

		static std::shared_ptr<ShadowFrameBuffer> Create();

		uint32 GetTextureID() const;

	protected:
		uint32 TextureID;

	private:
	};
}