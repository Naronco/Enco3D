#ifndef __ENCO3D_ILIGHT_H_INCLUDED__
#define __ENCO3D_ILIGHT_H_INCLUDED__

#include "Enco3DDatatypes.h"
#include "SVector3.h"
#include "SColor4.h"

namespace enco
{
	namespace core
	{
		enum ELightTypes
		{
			eLIGHTTYPE_DIRECTIONAL,
			eLIGHTTYPE_POINT,
			eLIGHTTYPE_SPOT,
		};

		struct ILight
		{
			sint32 lightType;
			math::Vector3f32 position, direction;
			Color4f32 color;
			float32 intensity, range, cosCutoff;
		};
	}
}

#endif