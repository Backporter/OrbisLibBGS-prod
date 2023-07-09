#pragma once

#include "../B/BSInputDevice.h"

namespace ConsoleRE
{
	class BSKeyboardDevice : public BSInputDevice
	{
	public:
		BSKeyboardDevice();
		virtual ~BSKeyboardDevice();

		// add (BSKeyboardDevice)
		virtual void Unk_0A() = 0;
		virtual void Unk_0B() = 0;
	public:
	};
}