#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	struct FORM
	{
	public:
		uint32_t form;
		uint32_t length;
		uint32_t flags;
		uint32_t formID;
		uint32_t versionControl;
		uint16_t formVersion;
		uint16_t vcVersion;
	};
	static_assert(sizeof(FORM) == 0x18);

	struct FORM_GROUP
	{
	public:
		FORM     groupData;
		uint64_t groupOffset;
	};
	static_assert(sizeof(FORM_GROUP) == 0x20);
}