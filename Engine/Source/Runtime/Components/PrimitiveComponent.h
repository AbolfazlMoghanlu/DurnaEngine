#pragma once

#include "Runtime/Components/SceneComponent.h"

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
		PrimitiveComponent();
		~PrimitiveComponent();

		void Tick(float DeltaTime) override;

		void BindPreDraw(void (*InFunc)(PrimitiveComponent* InComponent, Shader* InShader));
		void UnbindPreDraw();

		void SetStaticMesh(StaticMesh* InMesh, bool bUV = false, bool bNormal = false, bool bColor = false);
		StaticMesh* GetStaticMesh() const;

		void SetMaterial(Material* InMaterial);
		Material* GetMaterial() const;

	private:
		StaticMesh* Mesh;
		Material* SourceMaterial;

		VertexBuffer* VB;
		VertexElementBuffer* EB;
		VertexArray* VA;

		void (*PreDrawFunc)(PrimitiveComponent* InComponent, Shader* InShader) = nullptr;

		friend class RenderCommands;
	};
}