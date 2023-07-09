#include "../../../../../../../OrbisUtil/include/FileSystem.h"
#include "../../../../../../../OrbisUtil/include/SystemWrapper.h"
#include "../../../../../../../OrbisUtil/include/FramerateTracker.h"

#include "../FrameUtil/PapyrusExtFrameUtil.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"


namespace PapyrusExtFrameUtil
{
	// I really hate doing this...
	using namespace ConsoleRE;

	float GetFramerate(StaticFunctionTag* tag)
	{
		return xUtilty::FrameUtil::Tracker::GetSingleton()->GetFrameRate();
	}

	float GetFrametime(StaticFunctionTag* tag)
	{
		return xUtilty::FrameUtil::Tracker::GetSingleton()->GetFrameTime();
	}

	bool RegisterFrameUtil(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetFramerate),   StaticFunctionTag, float> ("GetFrameRate",		 "FrameUtil", GetFramerate));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetFrametime),   StaticFunctionTag, float> ("GetFrameTime",		 "FrameUtil", GetFrametime));

		VM->SetCallableFromTasklets("FrameUtil", "GetFrameRate",			 true);
		VM->SetCallableFromTasklets("FrameUtil", "GetFrameTime",			 true);

		return true;
	}
}