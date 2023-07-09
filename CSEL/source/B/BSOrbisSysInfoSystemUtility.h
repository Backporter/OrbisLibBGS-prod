#pragma once
#include <stdint.h>
#include "../../../OrbisUtil/include//Relocation.h"

namespace ConsoleRE
{
	class BSOrbisSysInfoSystemUtility
	{
	public:
		virtual ~BSOrbisSysInfoSystemUtility();

		static inline BSOrbisSysInfoSystemUtility* GetSingleton()
		{
			typedef BSOrbisSysInfoSystemUtility*(*__GetSingleton)();
			Relocation<__GetSingleton> _GetSingleton(0x168DFC0);
			return _GetSingleton();
		}

	private:
	};
	static_assert(sizeof(BSOrbisSystemUtility) != 0, "class size mismatch");
}