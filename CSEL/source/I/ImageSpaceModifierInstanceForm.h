#pragma once

#include "../I/ImageSpaceModifierInstance.h"

namespace ConsoleRE
{
	class TESImageSpaceModifier;

	class ImageSpaceModifierInstanceForm : public ImageSpaceModifierInstance
	{
	public:
		~ImageSpaceModifierInstanceForm() override; 

		// override (ImageSpaceModifierInstance)
		bool                            Unk_25(void) override;
		void                            Apply() override;
		ImageSpaceModifierInstanceForm* IsForm() override;
		void                            PrintInfo(char* a_dstBuf) override;
	public:
		TESImageSpaceModifier*	imod;
		uint64_t				unk30;
		float					unk38;
		uint32_t				unk3C;
		uint64_t				unk40;
		uint32_t				unk48;
	};
	static_assert(sizeof(ImageSpaceModifierInstanceForm) == 0x50);
}