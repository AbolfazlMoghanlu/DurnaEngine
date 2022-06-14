#pragma once

#include "Runtime/Components/PrimitiveComponent.h"

namespace Durna
{
	class Texture;

	class BillboardComponent : public PrimitiveComponent
	{
	public:
		BillboardComponent(const std::string& InLabel);
		virtual ~BillboardComponent();
		
		virtual void Tick(float DeltaTime) override;

		Texture* GetTexture() const;
		void SetTexture(Texture* InTexture);
	
	protected:
		Texture* SourceTexture = nullptr;
		

	private:

	};
}