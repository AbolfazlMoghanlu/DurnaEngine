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
	//TODO: inherit from component class
	class PrimitiveComponent : public SceneComponent
	{
	public:
		void Tick(float DeltaTime) override;

		PrimitiveComponent(StaticMesh* InMesh, Material* InMaterial);
		~PrimitiveComponent();

	private:
		
		
		

	public:
		void UpdateVertexColor(const std::vector<float>& InVertexColor);

		StaticMesh* Mesh;
		Material* SourceMaterial;

		/** Mesh has its own vertex color, its just gonna work as a ref for instances.
		* each primitive component has its own vertex color.
		 */
		std::vector<float> OverridedVertexColor;

		VertexBuffer* VB;
		VertexElementBuffer* EB;
	};
}