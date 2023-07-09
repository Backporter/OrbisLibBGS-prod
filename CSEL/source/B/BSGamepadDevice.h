#pragma once

#include "../../../OrbisUtil/include/Macro.h"

#include "../B/BSTEvent.h"
#include "../B/BSInputDevice.h"

#include <stdint.h>

namespace ConsoleRE
{
	struct BSGamepadEvent;

	class BSGamepadDevice : public BSInputDevice, public BSTEventSource<BSGamepadEvent>
	{
	public:
		BSGamepadDevice();
		virtual ~BSGamepadDevice();
		
		// override (BSInputDevice)
		bool			 IsEnabled(void) override;

		// add
		virtual void	 SetVibration(float, float) = 0;
		virtual void	 Unk_0B();																			// { return; }
		virtual void	 Unk_0C();																			// { return; }
		virtual uint32_t Unk_0D();																			// { return 0; }
		virtual void	 ProcessRawInput(int32_t a_rawX, int32_t a_rawY, float& a_outX, float& a_outY);		// { .... }
		virtual void	 Unk_0F();																			// { return; }
	public:
		int32_t  userIndex; /* Handle... */
		bool	 connected;
		bool	 listeningForInput;
		uint16_t pad9C;
	};
	static_assert(offsetof(BSGamepadDevice, userIndex) == 0x94);
}