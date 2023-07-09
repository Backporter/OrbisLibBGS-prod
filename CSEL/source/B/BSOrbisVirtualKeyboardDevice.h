#pragma once

#include "../../../OrbisUtil/include//RelocationManager.h"

#include "../B/BSVirtualKeyboardDevice.h"

#include <stdint.h>

namespace ConsoleRE
{
	class BSOrbisVirtualKeyboardDevice : public BSVirtualKeyboardDevice
	{
	public:
		virtual ~BSOrbisVirtualKeyboardDevice();

		// override (BSIInputDevice)
		void Initialize() override;
		void Process(float) override;
		void Finalize() override;
		void Reset() override;

		// override (BSKeyboardDevice)
		void Unk_0A() override;
		void Unk_0B() override;

		// override (BSVirtualKeyboardDevice)
		void Unk_0C() override;
		void Unk_0D() override;
		void Unk_0E() override;
	public:
		void* UNK50;
		void* UNK58;
		void* UNK60;
		void* UNK68;
		void* UNK70;
	};
	static_assert(sizeof(BSOrbisVirtualKeyboardDevice) == 0x78, "#");
}