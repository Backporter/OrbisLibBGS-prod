#pragma once

namespace ConsoleRE
{
	namespace BGSBodyPartDefs
	{
		struct LIMB_ENUMS
		{
			enum LIMB_ENUM
			{
				kNone = -1,
				kTorso = 0,
				kHead,
				kEye,
				kLookAt,
				kFlyGrab,
				kSaddle,
				kTotal
			};
		};
		using LIMB_ENUM = LIMB_ENUMS::LIMB_ENUM;
	}
}