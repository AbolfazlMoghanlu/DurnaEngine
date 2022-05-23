#pragma once

#include "Runtime/Renderer/FrameBuffer/FrameBuffer.h"

namespace Durna
{
	class ResolveDefferedBuffer : public FrameBuffer
	{
	public:
		ResolveDefferedBuffer();
		virtual ~ResolveDefferedBuffer();

		static std::shared_ptr<ResolveDefferedBuffer> Create();

		uint32 GetTextureID() const;

	protected:

	private:
		uint32 TextureID;
	};
}

