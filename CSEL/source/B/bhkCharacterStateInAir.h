#pragma once

#include "../B/bhkCharacterState.h"

namespace ConsoleRE
{
	class bhkCharacterStateInAir : public bhkCharacterState
	{
	public:
		~bhkCharacterStateInAir() override;

		// override (bhkCharacterState)
		hkpCharacterStateType GetType() const override;
		void                  Unk_10(void) override;
	public:
		uint64_t unk10;
	};
	static_assert(sizeof(bhkCharacterStateInAir) == 0x18);
}
