#include "../../../../../../../OrbisUtil/include//FileSystem.h"
#include "../../../../../../../OrbisUtil/include/SystemWrapper.h"
#include "../../../../../../../OrbisUtil/include/MemoryUsageTracker.h"

#include "../Memory/PapyrusExtMemory.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"


namespace PapyrusExtMemory
{
	// I really hate doing this...
	using namespace ConsoleRE;

	uint32_t GetFree(StaticFunctionTag* tag)
	{
		auto ret = xUtilty::MemoryUtil::MemoryUsageTracker::GetSingleton()->GetCurrentFreeMemory();
		PRINT_FMT("0x%lx", ret);
		return ret;
	}

	uint32_t GetUsed(StaticFunctionTag* tag)
	{
		auto ret = xUtilty::MemoryUtil::MemoryUsageTracker::GetSingleton()->GetCurrentAllocatedMemory();
		PRINT_FMT("0x%lx", ret);
		return ret;
	}

	bool RegisterMemory(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetFree),   StaticFunctionTag, uint32_t> ("GetFreeMemory",		 "Memory", GetFree));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetUsed),   StaticFunctionTag, uint32_t> ("GetUsedMemory",		 "Memory", GetUsed));

		VM->SetCallableFromTasklets("Memory", "GetFreeMemory",			 true);
		VM->SetCallableFromTasklets("Memory", "GetUsedMemory",			 true);

		return true;
	}
}