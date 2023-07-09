#pragma once

#include "../T/TESForm.h"
#include "../T/TESBoundObject.h"
#include "../N/NiPointer.h"

namespace ConsoleRE
{
	class TESForm;
	class TESBoundObject;
	class NiAVObject;

	struct Inventory3DItem
	{
	public:
		TESForm*              itemBase;
		TESBoundObject*       modelObj;
		NiPointer<NiAVObject> spModel;
		uint64_t			  unk18;
	};
	static_assert(sizeof(Inventory3DItem) == 0x20);
}