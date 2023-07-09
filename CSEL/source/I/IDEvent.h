#pragma once

#include "../B/BSFixedString.h"
#include "../I/InputEvent.h"

#include <stdint.h>

namespace ConsoleRE
{
	class IDEvent : public InputEvent
	{
	public:
		~IDEvent() override;

		bool					HasIDCode(void) override;
		const BSFixedString&	QUserEvent() override;

		constexpr uint32_t GetIDCode() const noexcept { return idCode; }
	public:
		BSFixedString userEvent;
		uint32_t	  idCode;
		uint32_t	  pad24;
	};
	static_assert(sizeof(IDEvent) == 0x28);
}