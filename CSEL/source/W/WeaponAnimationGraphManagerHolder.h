#pragma once

#include "../B/BShkbAnimationGraph.h"
#include "../B/BSTSmartPointer.h"
#include "../B/BSIntrusiveRefCounted.h"
#include "../B/BSAnimationGraphManager.h"
#include "../I/IAnimationGraphManagerHolder.h"

namespace ConsoleRE
{
	// 0x18
	class WeaponAnimationGraphManagerHolder : public IAnimationGraphManagerHolder, public BSIntrusiveRefCounted
	{
	public:
		// override (IAnimationGraphManagerHolder)
		bool GetAnimationGraphManagerImpl(BSTSmartPointer<BSAnimationGraphManager>&) override;
		bool SetAnimationGraphManagerImpl(BSTSmartPointer<BSAnimationGraphManager>&) override;
		bool ConstructAnimationGraph(BSTSmartPointer<BShkbAnimationGraph>& a_out) override;
		
		// add
		virtual void Unk_20(void);
		virtual void Unk_21(void);
	public:
		BSTSmartPointer<BSAnimationGraphManager> animationGraphManager;
	};
	static_assert(sizeof(WeaponAnimationGraphManagerHolder) == 0x18); // allocated @ 0x12344E(1.09);
}