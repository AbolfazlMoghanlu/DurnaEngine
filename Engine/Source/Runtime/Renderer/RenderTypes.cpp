#include "DurnaPCH.h"
#include "RenderTypes.h"

namespace Durna
{
	std::string DisplayBufferToString(int32 InDisplayBuffer)
	{
		switch (InDisplayBuffer)
		{
		case 0:		return "FinalColor";
		case 1:		return "SceneColor";
		case 2:		return "BaseColor";
		case 3:		return "WorldNormal";
		case 4:		return "SceneDepth";
		case 5:		return "Stencil";
		case 6:		return "Specular";
		case 7:		return "Roughness";
		case 8:		return "Metallic";
		case 9:		return "AO";
		case 10:	return "Shading Model";

		default:	return "InvalidBuffer";
		}
	}

}