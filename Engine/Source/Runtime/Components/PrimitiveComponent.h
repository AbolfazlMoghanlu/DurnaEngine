#pragma once

#include "Runtime/Renderer/Shader.h"
#include "Runtime/Renderer/Buffer.h"

#include "Runtime/Engine/StaticMesh.h"

class StaticMesh;
class Shader;

namespace Durna
{
	/*
	 * A component that can have visual representation or physics collision. 
	 */
	//TODO: inherit from component class
	class PrimitiveComponent
	{
	public:
		PrimitiveComponent(StaticMesh* InMesh, Shader* InShader);

		~PrimitiveComponent();

	private:
		
		
		

	public:
		void UpdateVertexColor(const std::vector<float>& InVertexColor);

		StaticMesh* Mesh;

		// TODO: make material class wrapper
		/** Shader that gonna shade the visual */
		std::shared_ptr<Shader> MeshShader;

		/** Mesh has its own vertex color, its just gonna work as a ref for instances.
		* each primitive component has its own vertex color.
		 */
		std::vector<float> OverridedVertexColor;

		VertexBuffer* VB;
		ElementBuffer* EB;

		bool bDirtyBuffer = true;
	};
}