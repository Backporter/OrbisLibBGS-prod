#pragma once

#include "../I/ImageSpaceModifierInstance.h"

namespace ConsoleRE
{
	class ImageSpaceModifierInstanceTemp : public ImageSpaceModifierInstance
	{
	public:
		~ImageSpaceModifierInstanceTemp() override;

		// override (ImageSpaceModifierInstance)
		bool Unk_25(void) override;
		void PrintInfo(char* a_dstBuf) override;
	public:
		float duration;
	};
	static_assert(sizeof(ImageSpaceModifierInstanceTemp) == 0x30);
}