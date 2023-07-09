#pragma once

#include "../T/TESTexture.h"

namespace ConsoleRE
{
	class TESTexture1024 : public TESTexture
	{
	public:
		~TESTexture1024() override;
		
		// override (TESTexture)
		uint32_t GetMaxAllowedSize() override;
	};
	static_assert(sizeof(TESTexture1024) == 0x10);
}