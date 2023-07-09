#pragma once

#include "../B/bhkCharacterState.h"

namespace ConsoleRE
{
	class bhkCharacterStateSwimming : public bhkCharacterState
	{
	public:
		~bhkCharacterStateSwimming() override;

		// override (bhkCharacterState)
		hkpCharacterStateType GetType() const override;
		void                  Unk_10(void) override;
	};
	static_assert(sizeof(bhkCharacterStateSwimming) == 0x10);
}
