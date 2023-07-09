#include "../../../../../../../OrbisUtil/include/GPU.h"

#include "../GPU/PapyrusExtGPU.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"

namespace PapyrusExtGPU
{
	// I really hate doing this...
	using namespace ConsoleRE;

	uint32_t GetGPUClockSpeed(StaticFunctionTag* tag)
	{
		uint32_t ret = xUtilty::GPU::GetFrequency();
		return ret;
	}

	bool RegisterGPU(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetGPUClockSpeed),   StaticFunctionTag, uint32_t> ("GetFrequency", "GPU", GetGPUClockSpeed));

		VM->SetCallableFromTasklets("GPU", "GetFrequency",	true);

		return true;
	}
}