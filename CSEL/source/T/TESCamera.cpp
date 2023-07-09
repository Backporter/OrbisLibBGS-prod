#include "../T/TESCamera.h"

#include "../T/TESCameraState.h"

namespace ConsoleRE
{
	void TESCamera::SetState(TESCameraState* a_rhs)
	{
		using func_t = decltype(&TESCamera::SetState);
		Relocation<func_t> func("", 0x5CCA80);
		return func(this, a_rhs);
	}

	void TESCamera::SetState_Impl(TESCameraState* a_rhs)
	{
		TESCameraState* a_var = 0;

		if (currentState.T1)
		{
			currentState.T1->End();
			a_var = currentState.T1;
		}

		if (a_var == a_rhs)
			a_rhs = currentState.T1;

		if (a_rhs)
			__sync_add_and_fetch(&a_rhs->refcount, 1);

		currentState.T1 = a_rhs;

		if (a_var)
		{
			uint32_t val = __sync_fetch_and_add(&a_var->refcount, 0x0FFFFFFFF);
			if (val == 1)
				delete a_var;
		}

		if (a_rhs)
			a_rhs->Begin();
	}
}