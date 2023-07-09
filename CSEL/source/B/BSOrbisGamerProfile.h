#pragma once
#include <stdint.h>
#include "../../../OrbisUtil/include//Relocation.h"

namespace ConsoleRE
{
	class BSOrbisGamerProfile
	{
	public:
		virtual ~BSOrbisGamerProfile();

		static inline BSOrbisGamerProfile* GetSingleton()
		{
			typedef BSOrbisGamerProfile*(*__GetSingleton)();
			static Relocation<__GetSingleton> _GetSingleton(0xE3EBF0);
			return _GetSingleton();
		}
	private:
	};
	static_assert(sizeof(BSOrbisGamerProfile) != 0, "class size mismatch");
}