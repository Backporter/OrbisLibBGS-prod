#pragma once

#include <stdint.h>

#include "../../../OrbisUtil/include//Relocation.h"

namespace ConsoleRE
{
	class BSORBISAwardsSystemUtility
	{
	public:
		virtual ~BSORBISAwardsSystemUtility();			// 0/8
		virtual void Unk_00(void);						// 16
		virtual void Unk_01(void);						// 24
		virtual void Unk_02(void);						// 32
		virtual void Unk_03(void);						// 40
		virtual void UnlockAchievement(int32_t ID);		// 48
		virtual void Unk_05(void);						// 56
		virtual void Unk_06(void);						// 64

		static inline BSORBISAwardsSystemUtility* GetSingleton()
		{
			typedef BSORBISAwardsSystemUtility*(*__GetSingleton)();
			static Relocation<__GetSingleton> _GetSingleton("BSORBISAwardsSystemUtility:GetSingleton", 0x1682B40);
			return _GetSingleton();
		}

		inline void UnlockTrophy(int32_t ID)
		{
			auto Singleton = GetSingleton();
			Singleton->UnlockAchievement(ID);
		}

		uint8_t Pad0[0xA];
		int32_t Context;
		uint8_t Pad1[0x28];
		int32_t handle;
	};
	static_assert(sizeof(BSORBISAwardsSystemUtility) != 0, "class size mismatch");
}
