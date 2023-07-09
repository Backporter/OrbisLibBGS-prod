#pragma once

namespace ConsoleRE
{
	struct INPUT_DEVICES
	{
		enum INPUT_DEVICE
		{
			kNone = -1,
			kKeyboard = 0,
			kMouse,
			kGamepad,
			kVirtualKeyboard,
			kTotal
		};
	};

	using INPUT_DEVICE = INPUT_DEVICES::INPUT_DEVICE;
}
