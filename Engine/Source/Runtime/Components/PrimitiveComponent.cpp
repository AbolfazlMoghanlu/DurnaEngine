#include "DurnaPCH.h"
#include "PrimitiveComponent.h"

#include "Runtime/Engine/StaticMesh.h"

namespace Durna
{
	PrimitiveComponent::PrimitiveComponent(StaticMesh* InMesh, Shader* InShader)
	{
		Mesh = InMesh;
		OverridedVertexColor = InMesh->VertexColors;

		VB = new VertexBuffer({
			VertexBufferLayout(&Mesh->VertexPositions, false, 3),
			VertexBufferLayout(&OverridedVertexColor, false, 4) });

		EB = new ElementBuffer(Mesh->VertexIndices);

		MeshShader.reset(InShader);
	}

	PrimitiveComponent::~PrimitiveComponent()
	{
		delete VB;
		delete EB;
	}

	void PrimitiveComponent::UpdateVertexColor(const std::vector<float>& InVertexColor)
	{
		OverridedVertexColor = InVertexColor;
		bDirtyBuffer = true;
	}

}