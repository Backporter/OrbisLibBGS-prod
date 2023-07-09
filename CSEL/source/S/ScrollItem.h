#pragma once
#include "../S/SpellItem.h"
#include "../T/TESModelTextureSwap.h"
#include "../B/BGSDestructibleObjectForm.h"
#include "../B/BGSPickupPutdownSounds.h"
#include "../T/TESWeightForm.h"
#include "../T/TESValueForm.h"


namespace ConsoleRE
{
	class ScrollItem :
		public SpellItem,
		public TESModelTextureSwap,
		public BGSDestructibleObjectForm,
		public BGSPickupPutdownSounds,
		public TESWeightForm,
		public TESValueForm
	{
	public:
		static constexpr int TypeID = 23;
		virtual ~ScrollItem();
	public:
	};
}