#pragma once

#include "Runtime/Engine/Image/Image.h"
#include "Runtime/Renderer/RenderTypes.h"

namespace Durna
{
	class Texture
	{
	protected:
		Texture();

	public:
		virtual ~Texture();

		virtual void Bind() const;
		void UnBind() const;
		virtual void UpdateTexture() = 0;
		
		static void ActivateTexture(uint8 Index);
		static uint32 GetGLTextureSlot(uint8 Index);

		EImageFormat InternalFormat = EImageFormat::RGB8;

	protected:
		unsigned int ID;
	};
}

