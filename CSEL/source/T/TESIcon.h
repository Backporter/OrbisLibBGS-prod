#pragma once

#include "../T/TESTexture.h"

namespace ConsoleRE
{
	class TESIcon : public TESTexture
	{
	public:
		~TESIcon() override;

		// override (TESTexture)
		const char* GetDefaultPath() override;
	};
	static_assert(sizeof(TESIcon) == 0x10);
}