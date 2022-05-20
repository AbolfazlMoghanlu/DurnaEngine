#pragma once

#include "Runtime/Components/SceneComponent.h"
#include "Runtime/Renderer/RenderTypes.h"

namespace Durna
{
	class StaticMesh;
	class Material;
	class Shader;
	class VertexBuffer;
	class VertexElementBuffer;
	class VertexArray;

	/*
	 * A component that can have visual representation or physics collision. 
	 */
	class PrimitiveComponent : public SceneComponent
	{
	public:
		PrimitiveComponent(const std::string& InLabel);
		virtual ~PrimitiveComponent();

		void Tick(float DeltaTime) override;

		void BindPreDraw(void (*InFunc)(PrimitiveComponent* InComponent, Shader* InShader));
		void UnbindPreDraw();

		void SetStaticMesh(StaticMesh* InMesh, bool bUV = false, bool bNormal = false, bool bColor = false);
		StaticMesh* GetStaticMesh() const;

		Material* GetMaterial() const;

		int32 StencilValue = 0;
		StencilMaskBitfield StencilMask = StencilMaskBitfield::Bit_None;

	private:
		StaticMesh* Mesh;
		std::unique_ptr<Material> SourceMaterial;
		
		std::unique_ptr<VertexBuffer> VB;
		std::unique_ptr<VertexElementBuffer> EB;
		std::unique_ptr<VertexArray> VA;

		void (*PreDrawFunc)(PrimitiveComponent* InComponent, Shader* InShader) = nullptr;

		friend class RenderCommands;

		// TODO: Remobe
		friend class Renderer;
	};
}