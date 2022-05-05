#include "DurnaPCH.h"
#include "PrimitiveComponent.h"

#include "Runtime/Engine/StaticMesh.h"
#include "Runtime/Renderer/Material.h"
#include "Runtime/Renderer/Shader.h"
#include "Runtime/Renderer/Buffer.h"

#include "Runtime/Renderer/RenderCommands.h"

namespace Durna
{
	void PrimitiveComponent::Tick(float DeltaTime)
	{
		SceneComponent::Tick(DeltaTime);

		if (Mesh)
		{
			RenderCommands::DrawPrimitive(*this);
		}
	}

	void PrimitiveComponent::BindPreDraw(void (*InFunc)(Shader* InShader))
	{
		PreDrawFunc = InFunc;
	}

	void PrimitiveComponent::UnbindPreDraw()
	{
		PreDrawFunc = nullptr;
	}

	void PrimitiveComponent::SetStaticMesh(StaticMesh* InMesh, bool bUV /*= false*/, bool bNormal /*= false*/, bool bColor /*= false*/)
	{
		Mesh = InMesh;
		VB->Clear();
		EB->Clear();

		if (Mesh)
		{
			VB->SetVertexCount(Mesh->VertexCount);
			VB->AddLayout(VertexBufferLayout(&Mesh->VertexPositions, 3, false));

			if (bUV)
			{
				VB->AddLayout(VertexBufferLayout(&Mesh->VertexUVs, 2, false));
			}

			if (bNormal)
			{
				VB->AddLayout(VertexBufferLayout(&Mesh->VertexNormal, 3, false));
			}

			if (bColor)
			{
				VB->AddLayout(VertexBufferLayout(&Mesh->VertexColors, 4, false));
			}

			VB->UpdateLayout();
			VB->Bind();
			VB->UpdateAttributes();

			EB->SetIndices(&Mesh->VertexIndices);
			EB->Bind();
			EB->UpdateBuffer();
		}
	}

	PrimitiveComponent::PrimitiveComponent()
	{
		Mesh = nullptr;
		SourceMaterial = nullptr;
		VB = new VertexBuffer;
		EB = new VertexElementBuffer;
	}

	PrimitiveComponent::~PrimitiveComponent()
	{
		delete VB;
		delete EB;
	}


	StaticMesh* PrimitiveComponent::GetStaticMesh() const
	{
		return Mesh;
	}

	void PrimitiveComponent::SetMaterial(Material* InMaterial)
	{
		SourceMaterial = InMaterial;
	}

	Material* PrimitiveComponent::GetMaterial() const
	{
		return SourceMaterial;
	}

}