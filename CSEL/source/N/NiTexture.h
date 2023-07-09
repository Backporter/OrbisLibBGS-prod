#pragma once

#include "../B/BSFixedString.h"
#include "../N/NiObject.h"

namespace ConsoleRE
{
	class NiTexture : public NiObject
	{
	public:
		NiTexture();
		virtual ~NiTexture();
	public:
		uint32_t				pixelLayout;
		uint32_t				alphaFormat;
		uint32_t				mipMapped;
		uint32_t				pad0C;
		BSFixedString			name;
		uint32_t				unk28;
		uint32_t				unk2C;
		NiTexture*				prev;
		NiTexture*				next;
	};
}