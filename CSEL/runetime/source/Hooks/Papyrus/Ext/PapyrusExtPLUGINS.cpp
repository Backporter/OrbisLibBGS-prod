#include "../Ext/PapyrusExtPLUGINS.h"

#include "../../../../../source/B/BSFixedString.h"
#include "../../../../../source/N/NativeFunction.h"

#if defined(__OPENORBIS__)
#include <orbis/libkernel.h>
#elif defined(__ORBIS__)
#include <kernel.h>
#endif

namespace PapyrusExtPLUGINS
{
	// I really hate doing this...
	using namespace ConsoleRE;

	int32_t		  GetPluginVersionType(StaticFunctionTag* tag, BSFixedString PluginName)   
	{ 
		return -1;
	}
	
	BSFixedString GetPluginVersionString(StaticFunctionTag* tag, BSFixedString PluginName)
	{
		return NULL;
	}

	int32_t		  GetPluginVersionInt(StaticFunctionTag* tag, BSFixedString PluginName)
	{
		return -1;
	}
	  
	float		  GetPluginVersionFloat(StaticFunctionTag* tag, BSFixedString PluginName)
	{
		return 0.0f;
	}

	int32_t		  GetPluginHandle(StaticFunctionTag* tag, BSFixedString PluginName)
	{ 
		return -1; 
	}
	
	int32_t		  UnloadPlugin(StaticFunctionTag* tag, BSFixedString PluginName)
	{
		return -1;
	}

	int32_t		  UnloadPluginH(StaticFunctionTag* tag, int32_t handle)
	{
		return -1;
	}

	int32_t		  LoadPlugin(StaticFunctionTag* tag, BSFixedString PluginName)
	{
		return 0;
	}

	int32_t		  LoadPluginC(StaticFunctionTag* tag, BSFixedString PluginName, BSFixedString PluginDirectory)
	{
		return 0;
	}

	bool RegisterPLUGINS(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(GetPluginVersionType),   StaticFunctionTag, int32_t,		BSFixedString>				  ("GetPluginVersionType",		"Plugin", GetPluginVersionType));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(GetPluginVersionString), StaticFunctionTag, BSFixedString, BSFixedString>				  ("GetPluginVersionString",	"Plugin", GetPluginVersionString));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(GetPluginVersionInt),	  StaticFunctionTag, int32_t,		BSFixedString>				  ("GetPluginVersionInt",		"Plugin", GetPluginVersionInt));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(GetPluginVersionFloat),  StaticFunctionTag, float,			BSFixedString>				  ("GetPluginVersionFloat",		"Plugin", GetPluginVersionFloat));

		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(GetPluginHandle),		  StaticFunctionTag, int32_t,		BSFixedString>				  ("GetPluginHandle",			"Plugin", GetPluginHandle));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(UnloadPlugin),			  StaticFunctionTag, int32_t,		BSFixedString>				  ("UnloadPlugin",				"Plugin", UnloadPlugin));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(UnloadPluginH),		  StaticFunctionTag, int32_t,		int32_t>					  ("UnloadPluginH",				"Plugin", UnloadPluginH));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(LoadPlugin),			  StaticFunctionTag, int32_t,		BSFixedString>				  ("LoadPlugin",				"Plugin", LoadPlugin));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(LoadPluginC),			  StaticFunctionTag, int32_t,		BSFixedString, BSFixedString> ("LoadPluginD",				"Plugin", LoadPluginC));

		return true;
	}
}