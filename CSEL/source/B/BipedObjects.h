#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	struct BIPED_OBJECTS
	{
		enum BIPED_OBJECT : uint32_t
		{
			kNone = static_cast<std::underlying_type_t<BIPED_OBJECT>>(-1),
			kHead = 0,
			kHair = 1,
			kBody = 2,
			kHands = 3,
			kForearms = 4,
			kAmulet = 5,
			kRing = 6,
			kFeet = 7,
			kCalves = 8,
			kShield = 9,
			kTail = 10,
			kLongHair = 11,
			kCirclet = 12,
			kEars = 13,
			kDecapitateHead = 20,
			kDecapitate = 21,
			kFX01 = 31,

			kEditorTotal = 32,

			kHandToHandMelee = kEditorTotal,
			kOneHandSword = 33,
			kOneHandDagger = 34,
			kOneHandAxe = 35,
			kOneHandMace = 36,
			kTwoHandMelee = 37,
			kBow = 38,
			kStaff = 39,
			kCrossbow = 40,
			kQuiver = 41,

			kTotal = 42
		};
	};
	using BIPED_OBJECT = BIPED_OBJECTS::BIPED_OBJECT;
}
