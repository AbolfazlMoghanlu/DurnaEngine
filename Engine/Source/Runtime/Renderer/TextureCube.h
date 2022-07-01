#pragma once

#include "Runtime/Renderer/Texture.h"

namespace Durna
{
	class TextureCube : public Texture
	{
	public:
		TextureCube(Image* InTopImage, Image* InBottomImage, Image* InRightImage, Image* InLeftImage,
			Image* InFrontImage, Image* InBackImage);

		TextureCube();
		virtual ~TextureCube();

		virtual void Bind() const override;

		virtual void UpdateTexture() override;

		void SetSources(Image* InTopImage, Image* InBottomImage, Image* InRightImage, Image* InLeftImage,
			Image* InFrontImage, Image* InBackImage);

		bool IsDirty() const;
		void MarkDirty();

	private:
		bool bDirtyFlag;

		Image* TopImage;
		Image* BottomImage;
		Image* RightImage;
		Image* LeftImage;
		Image* FrontImage;
		Image* BackImage;
	};
}