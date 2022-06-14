#pragma once

#include "Runtime/Renderer/Texture.h"
#include "Runtime/Renderer/RenderTypes.h"

namespace Durna
{
	class Shader;

	struct TextureElement
	{
		TextureElement(std::string InName, Texture* InTexture)
			: Name(InName), SourceTexture(InTexture)
		{}

		std::string Name;
		Texture* SourceTexture;
	};

	class Material
	{
	public:
		Material();
		Material(Shader* InShader);
		Material(Shader* InShader, uint32 TextureSlotSize);
		~Material();

		void Use();

		void SetShader(Shader* InShader);
		Shader* GetShader() const;

		void BindTextures();
		void AddTextureElement(const TextureElement& InElement);
		void ResetTextureElements();

		EShadingModel GetShadingModel() const;
		void SetShadingModel(EShadingModel InShadingModel);

	protected:
		EShadingModel ShadingModel = EShadingModel::DefaultLit; 

	private:
		Shader* SourceShader;
		std::vector<TextureElement> TextureElements;
	};
}