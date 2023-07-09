#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class BSOrbisAudioListener
	{
	public:
		virtual ~BSOrbisAudioListener();

		virtual void Unk00(void);	// sub_E1A0F0
		virtual void Unk01(void);	// sub_E1A110
		virtual void Unk02(void);	// nullsub_3344
		virtual void Unk03(void);	// sub_E1A1E0
		virtual void Unk04(void);	// sub_E16630
		virtual void Unk05(void);	// sub_E1A210

	private:
		uint8_t pad[0x40];
	};
	// 0x40
	static_assert(sizeof(BSOrbisAudioListener) != 0, "class size mismatch");
}