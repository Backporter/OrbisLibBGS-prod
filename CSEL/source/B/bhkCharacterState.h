#pragma once

#include "../H/hkpCharacterState.h"

namespace ConsoleRE
{
	class bhkCharacterState : public hkpCharacterState
	{
	public:
		~bhkCharacterState() override;

		// override (hkpCharacterState)
		void Update(hkpCharacterContext& a_context, const hkpCharacterInput& a_input, hkpCharacterOutput& a_output) override;
		void Change(hkpCharacterContext& a_context, const hkpCharacterInput& a_input, hkpCharacterOutput& a_output) override;

		// add
		virtual void Unk_10() = 0;
	};
	static_assert(sizeof(bhkCharacterState) == 0x10);
}