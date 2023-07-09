#pragma once

#include "../B/bhkCharacterState.h"

namespace ConsoleRE
{
	class bhkCharacterStateFlying : public bhkCharacterState
	{
	public:
		~bhkCharacterStateFlying() override;

		// override (bhkCharacterState)
		hkpCharacterStateType GetType() const override;
		void                  Unk_10(void) override;
	};
	static_assert(sizeof(bhkCharacterStateFlying) == 0x10);
}
