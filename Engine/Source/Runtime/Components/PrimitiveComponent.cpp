#include "DurnaPCH.h"
#include "PrimitiveComponent.h"

#include "Runtime/Engine/StaticMesh.h"
#include "Runtime/Renderer/Material.h"
#include "Runtime/Renderer/Buffer.h"

namespace Durna
{
	PrimitiveComponent::PrimitiveComponent(StaticMesh* InMesh, Material* InMaterial)
	{
		Mesh = InMesh;
		OverridedVertexColor = InMesh->VertexColors;

		VB = new VertexBuffer(Mesh->VertexCount);
		VB->AddLayout(VertexBufferLayout(&Mesh->VertexPositions, 3, false));
		VB->AddLayout(VertexBufferLayout(&OverridedVertexColor, 4, false));
		VB->AddLayout(VertexBufferLayout(&Mesh->VertexUVs, 2, false));
		VB->UpdateLayout();
		VB->Bind();
		VB->UpdateAttributes();

		EB = new VertexElementBuffer(Mesh->VertexIndices);
		EB->Bind();
		EB->UpdateBuffer();

		SourceMaterial = InMaterial;
	}

	PrimitiveComponent::~PrimitiveComponent()
	{
		delete VB;
		delete EB;
	}

	void PrimitiveComponent::UpdateVertexColor(const std::vector<float>& InVertexColor)
	{
		OverridedVertexColor = InVertexColor;
	}

}