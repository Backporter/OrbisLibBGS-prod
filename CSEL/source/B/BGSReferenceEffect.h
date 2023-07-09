#pragma once

#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSReferenceEffect : public TESForm 
	{
	public:
		struct Data
		{
		public:
			BGSArtObject*	 artObject;
			TESEffectShader* effectShader;
			uint32_t		 flags;
			uint32_t		 pad14;
		};
		static_assert(sizeof(Data) == 0x18);
	public:
		static constexpr int TypeID = 57;

		~BGSReferenceEffect() override;
	public:
		Data data;
	};
	static_assert(sizeof(BGSReferenceEffect) == 0x38);
}