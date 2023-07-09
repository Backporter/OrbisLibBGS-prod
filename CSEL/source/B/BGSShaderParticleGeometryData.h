#pragma once

#include "../B/BSTArray.h"
#include "../T/TESForm.h"
#include "../T/TESTexture.h"

#include <stdint.h>

namespace ConsoleRE
{
	union SETTING_VALUE
	{
		float       f;
		uint32_t	i;
	};
	static_assert(sizeof(SETTING_VALUE) == 0x4);

	class BGSShaderParticleGeometryData : public TESForm
	{
	public:
		static constexpr int TypeID = 56;
		
		~BGSShaderParticleGeometryData() override;
	public:
		BSTArray<SETTING_VALUE>	data;
		TESTexture              particleTexture;
	};
	static_assert(sizeof(BGSShaderParticleGeometryData) == 0x40);
}