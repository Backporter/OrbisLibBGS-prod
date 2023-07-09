#pragma once

#include "../N/NiObject.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class NiAVObject;
	class ImageSpaceModifierInstanceForm;

	class ImageSpaceModifierInstance : NiObject
	{
	public:
		~ImageSpaceModifierInstance() override;

		// add
		virtual bool                            Unk_25(void);
		virtual void                            Apply() = 0;
		virtual ImageSpaceModifierInstanceForm* IsForm();
		virtual void                            PrintInfo(char* a_dstBuf) = 0;
	public:
		uint32_t				unk10;
		float					strength;
		NiPointer<NiAVObject>	target;
		float					age;
		uint32_t				flags;
	};
	static_assert(sizeof(ImageSpaceModifierInstance) == 0x28);
}