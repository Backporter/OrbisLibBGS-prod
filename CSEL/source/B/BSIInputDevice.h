#pragma once

#include "../B/BSFixedString.h"

namespace ConsoleRE
{
	class BSIInputDevice
	{
	public:
		struct InputButton
		{
			BSFixedString name;
			float         heldDownSecs;
			uint32_t	  keycode;
		};
		static_assert(sizeof(InputButton) == 0x10);
	public:
		virtual ~BSIInputDevice() = default;

		// add
		virtual void			Initialize() = 0;
		virtual void			Process(float) = 0;
		virtual void			Finalize() = 0;
		virtual bool			GetKeyMapping(uint32_t, BSFixedString&) = 0;
		virtual uint32_t        GetMappingKey(BSFixedString) = 0;
		virtual bool			GetInputButton(uint32_t, InputButton*&) = 0;
		virtual bool 			IsEnabled() = 0;
		virtual void			Reset() = 0;
	public:
	};
	static_assert(sizeof(BSIInputDevice) == 0x8);
}