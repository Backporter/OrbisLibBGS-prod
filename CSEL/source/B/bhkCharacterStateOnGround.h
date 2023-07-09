#pragma once

#include "../B/bhkCharacterState.h"

namespace ConsoleRE
{
	class bhkCharacterStateOnGround : public bhkCharacterState
	{
	public:
		~bhkCharacterStateOnGround() override;

		// override (bhkCharacterState)
		hkpCharacterStateType GetType() const override;
		void                  Unk_10(void) override;
	public:
		uint64_t unk10;
	};
	static_assert(sizeof(bhkCharacterStateOnGround) == 0x18);
}
