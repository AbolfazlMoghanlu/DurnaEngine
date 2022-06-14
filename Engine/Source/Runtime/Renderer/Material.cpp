#include "DurnaPCH.h"
#include "Material.h"
#include "Runtime/Renderer/Shader.h"

LOG_DEFINE_CATEGORY(LogMaterial, "Material")

namespace Durna
{
	Material::Material(Shader* InShader, uint32 TextureSlotSize)
	{
		TextureElements.reserve(TextureSlotSize);
		SetShader(InShader);
	}

	Material::Material(Shader* InShader)
		: Material(InShader, 0)
	{}

	Material::Material()
		: Material(nullptr, 0)
	{}

	Material::~Material()
	{
		ResetTextureElements();
	}

	void Material::Use()
	{
		SourceShader->Use();
		BindTextures();
	}

	void Material::SetShader(Shader* InShader)
	{
		SourceShader = InShader;
	}

	Shader* Material::GetShader() const
	{
		return SourceShader;
	}

	void Material::BindTextures()
	{
		for (int32 i = 0; i < TextureElements.size(); i++)
		{
			const TextureElement& Element = TextureElements[i];

			Texture::ActivateTexture(i);
			Element.SourceTexture->Bind();
			Element.SourceTexture->UpdateTexture();

			SourceShader->SetUniform1i(Element.Name, i);
		}
	}

	void Material::AddTextureElement(const TextureElement& InElement)
	{
		for (const TextureElement Element : TextureElements)
		{
			if (InElement.Name.compare(Element.Name) == 0)
			{
				LOG(LogMaterial, Error,
					"Element with name \"%s\" was already in layout.\nFailed to add elemnent to texture layout.", Element.Name.c_str());
				return;
			}
		}

		TextureElements.push_back(InElement);
	}

	void Material::ResetTextureElements()
	{
		TextureElements.clear();
	}

	EShadingModel Material::GetShadingModel() const
	{
		return ShadingModel;
	}

	void Material::SetShadingModel(EShadingModel InShadingModel)
	{
		ShadingModel = InShadingModel;
	}
}