#pragma once

#include "../B/bhkCharacterState.h"

namespace ConsoleRE
{
	class bhkCharacterStateClimbing : public bhkCharacterState
	{
	public:
		~bhkCharacterStateClimbing() override;

		// override (bhkCharacterState)
		hkpCharacterStateType GetType() const override;
		void                  Unk_10(void) override;
	};
	static_assert(sizeof(bhkCharacterStateClimbing) == 0x10);
}
