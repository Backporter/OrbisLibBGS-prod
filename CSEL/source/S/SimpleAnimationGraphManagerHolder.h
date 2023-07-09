#pragma once

#include "../I/IAnimationGraphManagerHolder.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class SimpleAnimationGraphManagerLoadingTask;

	class SimpleAnimationGraphManagerHolder : public IAnimationGraphManagerHolder
	{
	public:
		// override (IAnimationGraphManagerHolder)
		bool GetAnimationGraphManagerImpl(BSTSmartPointer<BSAnimationGraphManager>& a_out) const override;
		bool SetAnimationGraphManagerImpl(BSTSmartPointer<BSAnimationGraphManager>& a_in) override;
		bool ConstructAnimationGraph(BSTSmartPointer<BShkbAnimationGraph>& a_out) override;
	public:
		BSTSmartPointer<BSAnimationGraphManager>          animationGraphManager;
		NiPointer<SimpleAnimationGraphManagerLoadingTask> loadingTask;
	};
	static_assert(sizeof(SimpleAnimationGraphManagerHolder) == 0x18);

}