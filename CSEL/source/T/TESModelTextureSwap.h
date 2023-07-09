#pragma once

#include "../B/BSFixedString.h"
#include "../T/TESModel.h"

#include <stdint.h>

namespace ConsoleRE
{
	class BGSTextureSet;

	// 
	class TESModelTextureSwap : public TESModel
	{
	public:
		struct AlternateTexture
		{
			BGSTextureSet*	textureSet;
			uint32_t		index3D;
			uint32_t		Unk0C;
			BSFixedString	name;
		};
		static_assert(sizeof(AlternateTexture) == 0x18);
	public:
		~TESModelTextureSwap() override;

		// override (TESModel)
		void				 InitializeDataComponent() override;
		void				 ClearDataComponent() override;
		void				 CopyComponent(BaseFormComponent* a_rhs) override;
		TESModelTextureSwap* GetAsModelTextureSwap() override;
	public:
		AlternateTexture*	alternateTextures;
		uint32_t			numAlternateTextures;
	};
	static_assert(sizeof(TESModelTextureSwap) == 0x38);
}