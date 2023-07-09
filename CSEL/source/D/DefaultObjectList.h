#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

namespace ConsoleRE
{
	class DefaultObjectList
	{
	public:
		struct Object
		{
			const char* Unk00;
			uint32_t	Unk08;
			uint32_t	Unk0C;
			uint32_t	Unk10;
			uint32_t	Unk14;
		};
		static_assert(sizeof(Object) == 0x18, "");
	public:
		DefaultObjectList() = delete;
		~DefaultObjectList() = delete;

		static DefaultObjectList* GetSingleton()
		{
			Relocation<DefaultObjectList**> singleton("", 0x208AAB0);
			return *singleton;
		}
	public:
		Object Unk00[0x15B];
	};
}