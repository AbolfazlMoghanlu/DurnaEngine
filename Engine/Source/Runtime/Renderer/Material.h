#pragma once

#include "Runtime/Renderer/Texture.h"

namespace Durna
{
	class Shader;

	struct TextureElement
	{
		TextureElement(std::string InName, ETextureSlot InSlot, Texture* InTexture)
			: Name(InName), TextureSlot(InSlot), SourceTexture(InTexture)
		{}

		std::string Name;
		ETextureSlot TextureSlot;
		Texture* SourceTexture;
	};

	class Material
	{
	public:
		Material();
		Material(Shader* InShader);
		Material(Shader* InShader, uint32 TextureSlotSize);
		~Material();

		void SetShader(Shader* InShader);
		Shader* GetShader() const;

		void BindTextures();
		void AddTextureElement(const TextureElement& InElement);
		void ResetTextureElements();

	private:
		Shader* SourceShader;
		std::vector<TextureElement> TextureElements;
	};
}


