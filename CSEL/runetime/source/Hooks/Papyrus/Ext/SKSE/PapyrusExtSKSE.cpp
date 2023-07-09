#include "../SKSE/PapyrusExtSKSE.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"

#include "../../../../../../runetime/Internal/PluginManger.h"

namespace PapyrusExtSKSE
{
	// I really hate doing this...
	using namespace ConsoleRE;

	int32_t			SKSEGetVersion(StaticFunctionTag* tag)			{ return 2; }
	int32_t			SKSEGetVersionMinor(StaticFunctionTag* tag)		{ return 0; }
	int32_t			SKSEGetVersionBeta(StaticFunctionTag* tag)		{ return 17; }
	int32_t			SKSEGetVersionRelease(StaticFunctionTag* tag)	{ return 65; }
	
	uint32_t GetPluginVersion(StaticFunctionTag* base, BSFixedString name)
	{
		PluginInfo* info = Internal::PluginManger::GetSingleton()->GetPluginInfoByName(name.c_str());
		if (info) 
		{
			return info->GetPluginVersion();
		}
	
		return -1;
	}

	bool RegisterSKSE(ConsoleRE::BSScript::Internal::VirtualMachine* a_vm)
	{

		a_vm->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SKSEGetVersion),				StaticFunctionTag, int32_t>						("GetVersion",			"SKSE", SKSEGetVersion));
		a_vm->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SKSEGetVersionMinor),			StaticFunctionTag, int32_t>						("GetVersionMinor",		"SKSE", SKSEGetVersionMinor));
		a_vm->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SKSEGetVersionBeta),			StaticFunctionTag, int32_t>						("GetVersionBeta",		"SKSE", SKSEGetVersionBeta));
		a_vm->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SKSEGetVersionRelease),		StaticFunctionTag, int32_t>						("GetVersionRelease",	"SKSE", SKSEGetVersionRelease));
		a_vm->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetPluginVersion),			StaticFunctionTag, uint32_t, BSFixedString>		("GetPluginVersion",	"SKSE", GetPluginVersion));

		return true;
	}
}