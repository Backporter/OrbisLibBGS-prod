#pragma once

#include "../I/IMovementInterface.h"

namespace ConsoleRE
{
	class IMovementState : public IMovementInterface
	{
	public:
		~IMovementState() override;

		virtual void Unk_02(void) = 0;
		virtual void Unk_03(void) = 0;
		virtual void Unk_04(void) = 0;
		virtual void Unk_05(void) = 0;
		virtual void Unk_06(void) = 0;
		virtual void Unk_07(void) = 0;
		virtual void Unk_08(void) = 0;
		virtual void Unk_09(void) = 0;
		virtual void Unk_10(void) = 0;
		virtual void Unk_11(void) = 0;
		virtual void Unk_12(void) = 0;
		virtual void Unk_13(void) = 0;
		virtual void Unk_14(void) = 0;
		virtual void Unk_15(void) = 0;
		virtual void Unk_16(void) = 0;
		virtual void Unk_17(void) = 0;
		virtual void Unk_18(void) = 0;
		virtual void Unk_19(void) = 0;
		virtual void Unk_20(void) = 0;
	public:
	};
	static_assert(sizeof(IMovementState) == 0x8);
}