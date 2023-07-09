#pragma once

#include "../B/bhkCharacterState.h"

namespace ConsoleRE
{
	class bhkCharacterStateJumping : public bhkCharacterState
	{
	public:
		~bhkCharacterStateJumping() override;

		// override (bhkCharacterState)
		hkpCharacterStateType GetType() const override;
		void                  Unk_10(void) override;
	};
	static_assert(sizeof(bhkCharacterStateJumping) == 0x10);
}
