#pragma once

#include "../B/BGSPreloadable.h"
#include "../T/TESBoundObject.h"
#include "../T/TESEnchantableForm.h"
#include "../T/TESFullName.h"
#include "../T/TESImageSpaceModifiableForm.h"
#include "../T/TESModel.h"


namespace ConsoleRE
{
	class BGSExplosion : public TESBoundObject, public TESFullName, public TESModel, public TESEnchantableForm, public BGSPreloadable, public TESImageSpaceModifiableForm
	{
	public:
		static constexpr int TypeID = 87;
	};
}