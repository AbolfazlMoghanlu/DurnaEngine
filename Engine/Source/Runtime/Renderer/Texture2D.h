#pragma once

#include "Runtime/Renderer/Texture.h"

namespace Durna
{
	class Texture2D : public Texture
	{
	public:
		Texture2D(Image* Img);

		virtual void Bind() const override;

		virtual void UpdateTexture() override;

		void SetSource(Image* Img);
		Image* GetSource() const;

		bool IsDirty() const;
		void MarkDirty();

	private:
		Image* SourceImage;
		bool bDirtyFlag;
	};
}