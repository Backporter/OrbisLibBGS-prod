#pragma once

#include "../B/BSKeyboardDevice.h"

namespace ConsoleRE
{
	class BSVirtualKeyboardDevice :	public BSKeyboardDevice
	{
	public:
		BSVirtualKeyboardDevice();
		virtual ~BSVirtualKeyboardDevice();

		void Unk_0A() override; // { return; }
		void Unk_0B() override; // { return; }

		virtual void Unk_0C() = 0;
		virtual void Unk_0D() = 0;
		virtual void Unk_0E() = 0;
	public:
	};
}