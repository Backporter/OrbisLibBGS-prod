#pragma once

#include "../../../OrbisUtil/include/Macro.h"

#include "../B/BSGamepadDevice.h"
#include "../B/BSInputDevice.h"

#include <stdint.h>
#include <stddef.h>

#if defined(__ORBIS__)
#include <pad.h>
#elif defined(__OPENORBIS__)
#include <orbis/Pad.h>
typedef OrbisPadData ScePadData;

typedef enum ScePadButtonDataOffset
{
	SCE_PAD_BUTTON_L3 = 0x00000002,
	SCE_PAD_BUTTON_R3 = 0x00000004,
	SCE_PAD_BUTTON_OPTIONS = 0x00000008,
	SCE_PAD_BUTTON_UP = 0x00000010,
	SCE_PAD_BUTTON_RIGHT = 0x00000020,
	SCE_PAD_BUTTON_DOWN = 0x00000040,
	SCE_PAD_BUTTON_LEFT = 0x00000080,
	SCE_PAD_BUTTON_L2 = 0x00000100,
	SCE_PAD_BUTTON_R2 = 0x00000200,
	SCE_PAD_BUTTON_L1 = 0x00000400,
	SCE_PAD_BUTTON_R1 = 0x00000800,
	SCE_PAD_BUTTON_TRIANGLE = 0x00001000,
	SCE_PAD_BUTTON_CIRCLE = 0x00002000,
	SCE_PAD_BUTTON_CROSS = 0x00004000,
	SCE_PAD_BUTTON_SQUARE = 0x00008000,
	SCE_PAD_BUTTON_TOUCH_PAD = 0x00100000,
	SCE_PAD_BUTTON_INTERCEPTED = 0x80000000,
} ScePadButtonDataOffset;

typedef ScePadButtonDataOffset OrbisPadButtonDataOffset;
#endif

namespace ConsoleRE
{
	class BSOrbisGamepadDevice : public BSGamepadDevice
	{
	public:
		using Keys = ScePadButtonDataOffset;
	public:
		BSOrbisGamepadDevice();
		virtual ~BSOrbisGamepadDevice();

		// override (BSIInputDevice)
		void Initialize() override;
		void Process(float) override;
		void Finalize() override;
		void Reset() override;

		// override (BSGamepadDevice)
		void	 SetVibration(float, float) override;
		uint32_t Unk_0D() override;
		void	 ProcessRawInput(int32_t a_rawX, int32_t a_rawY, float& a_outX, float& a_outY) override;
		void	 Unk_0F() override;
	public:
		ScePadData	PadData;
		void*		UNK118;
		void*		UNK120;
		void*		UNK128;
		ScePadData	PadData2;
		void*		UNK1A8;
		void*		UNK1B0;
		void*		UNK1B8;
		void*		UNK1C0;
	};
	static_assert(offsetof(BSOrbisGamepadDevice, PadData)  == 0xA0);
	static_assert(offsetof(BSOrbisGamepadDevice, PadData2) == 0x130);
	static_assert(sizeof(BSOrbisGamepadDevice) == 0x1C8);
}