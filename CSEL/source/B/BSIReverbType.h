#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class BSIReverbType 
	{
	public:
		virtual int32_t	DoGetRoomLevel() const = 0;
		virtual int32_t	DoGetRoomHFLevel() const = 0;
		virtual float	DoGetDecayTime() const = 0;
		virtual float	DoGetDecayHFRatio() const = 0;
		virtual int32_t	DoGetReflectionLevel() const = 0;
		virtual float	DoGetReflectionDelay() const = 0;
		virtual int32_t	DoGetReverbLevel() const = 0;
		virtual float	DoGetReverbDelay() const = 0;
		virtual float	DoGetDiffusion() const = 0;
		virtual float	DoGetDensity() const = 0;
		virtual float	DoGetHFReference() const = 0;
	};
	static_assert(sizeof(BSIReverbType) == 0x8);
}