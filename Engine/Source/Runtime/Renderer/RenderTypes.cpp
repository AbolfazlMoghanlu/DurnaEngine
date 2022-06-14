#include "DurnaPCH.h"
#include "RenderTypes.h"

namespace Durna
{
	std::string DisplayBufferToString(int32 InDisplayBuffer)
	{
		switch (InDisplayBuffer)
		{
		case 0:		return "FinalColor";
		case 1:		return "BaseColor";
		case 2:		return "WorldNormal";
		case 3:		return "SceneDepth";
		case 4:		return "Stencil";
		case 5:		return "Specular";
		case 6:		return "Roughness";
		case 7:		return "Metallic";
		case 8:		return "AO";
		case 9:		return "Shading Model";

		default:	return "InvalidBuffer";
		}
	}

}