#pragma once

#include "Runtime/Components/SceneComponent.h"

namespace Durna
{
	class StaticMesh;
	class Material;
	class VertexBuffer;
	class VertexElementBuffer;

	/*
	 * A component that can have visual representation or physics collision. 
	 */
	class PrimitiveComponent : public SceneComponent
	{
	public:
		PrimitiveComponent();
		~PrimitiveComponent();

		void Tick(float DeltaTime) override;

		void SetStaticMesh(StaticMesh* InMesh, bool bUV = false, bool bNormal = false, bool bColor = false);
		StaticMesh* GetStaticMesh() const;

		void SetMaterial(Material* InMaterial);
		Material* GetMaterial() const;


		

	private:
		StaticMesh* Mesh;
		Material* SourceMaterial;

		VertexBuffer* VB;
		VertexElementBuffer* EB;

		friend class RenderCommands;
	};
}