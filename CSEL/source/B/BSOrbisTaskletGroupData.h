#pragma once
#include <stdint.h>

namespace ConsoleRE
{
	class BSOrbisTaskletGroupData
	{
	public:
		virtual ~BSOrbisTaskletGroupData();
	private:
		uint8_t pad[0x38];
	};
	// 0x38
	static_assert(sizeof(BSOrbisTaskletGroupData) != 0, "class size mismatch");
}