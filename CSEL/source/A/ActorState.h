#pragma once

#include "../I/IMovementState.h"

#include <stdint.h>

namespace ConsoleRE
{
	class ActorState : public IMovementState
	{
	public:
		struct ActorState1
		{
		public:
			uint32_t			movingBack : 1;        // 0:00
			uint32_t			movingForward : 1;     // 0:01
			uint32_t			movingRight : 1;       // 0:02
			uint32_t			movingLeft : 1;        // 0:03
			uint32_t			unk04 : 2;             // 0:04
			uint32_t			walking : 1;           // 0:06
			uint32_t			running : 1;           // 0:07
			uint32_t			sprinting : 1;         // 0:08
			uint32_t			sneaking : 1;          // 0:09
			uint32_t			swimming : 1;          // 0:10
			uint32_t			unk11 : 3;             // 0:11
			uint32_t			sitSleepState : 4;     // 0:14
			uint32_t			flyState : 3;          // 0:18
			uint32_t			lifeState : 4;         // 0:21
			uint32_t			knockState : 3;        // 0:25
			uint32_t			meleeAttackState : 4;  // 0:28
		};
		static_assert(sizeof(ActorState1) == 0x4);

		struct ActorState2
		{
		public:
			uint32_t talkingToPlayer : 1;  // 0:00
			uint32_t forceRun : 1;         // 0:01
			uint32_t forceSneak : 1;       // 0:02
			uint32_t headTracking : 1;     // 0:03
			uint32_t reanimating : 1;      // 0:04
			uint32_t weaponState : 3;      // 0:05
			uint32_t wantBlocking : 1;     // 0:08
			uint32_t flightBlocked : 1;    // 0:09
			uint32_t recoil : 2;           // 0:10
			uint32_t allowFlying : 1;      // 0:12
			uint32_t staggered : 1;        // 0:13
			uint32_t unk14 : 18;           // 0:14
		};
		static_assert(sizeof(ActorState2) == 0x4);
	public:
		~ActorState() override;
	
		void Unk_02(void) override;
		void Unk_03(void) override;
		void Unk_04(void) override;
		void Unk_05(void) override;
		void Unk_06(void) override;
		void Unk_07(void) override;
		void Unk_08(void) override;
		void Unk_09(void) override;

		// add
		virtual void Unk_14(void);
		virtual void Unk_15(void);

		uint32_t GetAttackState()	const noexcept { return actorState1.meleeAttackState;	}
		uint32_t GetFlyState()		const noexcept { return actorState1.flyState;			}
		uint32_t GetKnockState()	const noexcept { return actorState1.knockState;			}
		uint32_t GetLifeState()		const noexcept { return actorState1.lifeState;			}
		uint32_t GetSitSleepState() const noexcept { return actorState1.sitSleepState;		}
		uint32_t GetWeaponState()	const noexcept { return actorState2.weaponState;		}

		bool	 IsSneaking()		const noexcept { return static_cast<bool>(actorState1.sneaking);	}
		bool	 IsSprinting()		const noexcept { return static_cast<bool>(actorState1.sprinting);	}
		bool	 IsSwimming()		const noexcept { return static_cast<bool>(actorState1.swimming);	}

		bool	 IsUnconscious()	const noexcept { return GetLifeState() == 3;																	}
		bool	 IsBleedingOut()	const noexcept { return GetLifeState() == 7 || GetLifeState() == 8 ? true : false;								}
		bool	 IsFlying()			const noexcept { return GetFlyState() == 0 || GetFlyState() == 5 ? false : true;								}
		bool	 IsWeaponDrawn()	const noexcept { return GetWeaponState() == 3 || GetWeaponState() == 4 || GetWeaponState() == 5 ? true : false; }
	public:
		ActorState1 actorState1;
		ActorState2 actorState2;
	};
	static_assert(sizeof(ActorState) == 0x10, "#####");
}