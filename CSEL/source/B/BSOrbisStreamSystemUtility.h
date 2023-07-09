#pragma once
#include <stdint.h>
#include "../../../OrbisUtil/include//Relocation.h"

namespace ConsoleRE
{
	class BSOrbisSystemUtility
	{
	public:
		virtual ~BSOrbisSystemUtility();

		static inline BSOrbisSystemUtility* GetSingleton()
		{
			typedef BSOrbisSystemUtility*(*__GetSingleton)();
			Relocation<__GetSingleton> GetSingleton(0x1684040);
			return GetSingleton();
		}
	private:
	};
	static_assert(sizeof(BSOrbisSystemUtility) != 0, "class size mismatch");
}