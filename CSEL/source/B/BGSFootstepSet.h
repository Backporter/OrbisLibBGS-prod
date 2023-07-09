#pragma once

#include "../B/BSTArray.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSFootstep;

	struct ACTOR_MOVEMENT_TYPES
	{
		enum ACTOR_MOVEMENT_TYPE : uint32_t
		{
			kWalk = 0,
			kRun = 1,
			kSneak = 2,
			kBleedout = 3,
			kSwim = 4,

			kTotal = 5
		};
	};
	using ACTOR_MOVEMENT_TYPE = ACTOR_MOVEMENT_TYPES::ACTOR_MOVEMENT_TYPE;

	class BGSFootstepSet : public TESForm
	{
	public:
		static constexpr int TypeID = 111;

		~BGSFootstepSet() override;
	public:
		BSTArray<BGSFootstep*> entries[ACTOR_MOVEMENT_TYPES::kTotal];
	};
}