#include "../../../../../../OrbisUtil/include/MessageHandler.h"
#include "../../../../../../OrbisUtil/include/DialogueManger.h"

#include "../Ext/PapyrusExtPS4.h"

#include "../../../../../source/B/BSFixedString.h"
#include "../../../../../source/N/NativeFunction.h"


#if defined(__ORBIS__)
#include <system_service.h>
#elif defined(__OPENORBIS__)
#include <orbis/SystemService.h>
#endif

namespace PapyrusExtPS4
{
	using namespace ConsoleRE;

	char UserInput[2048] { 0 };

	void PapyrusNotify(ConsoleRE::StaticFunctionTag* tag,       ConsoleRE::BSFixedString Message) { xUtilty::Notify(Message.c_str());				}
	void PapyrusKernelPrintt(ConsoleRE::StaticFunctionTag* tag, ConsoleRE::BSFixedString Message) { xUtilty::KernelPrintOut(Message.c_str());		}
	void QuickQuit(ConsoleRE::StaticFunctionTag* tag)											  { sceSystemServiceLoadExec("exit", nullptr);		}
	
	BSFixedString GetUserInput(ConsoleRE::StaticFunctionTag*, ConsoleRE::BSFixedString Title, ConsoleRE::BSFixedString ExampleText)
	{
		memset(UserInput, 0, sizeof(UserInput));
		auto Singleton = xUtilty::DialogueManger::OrbisDialogueManger::GetSingleton();
		Singleton->InitializeImeDialog("Hello From papyrus! [TITLE]", "HELLO FROM PAPYRUS! [EXAMPLE TEXT]");
		Singleton->ShowImeDialog(UserInput);
		return UserInput;
	}

	// 
	bool RegisterPS4(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(QuickQuit),				ConsoleRE::StaticFunctionTag, void>																		   ("VSH",		 "PS4", QuickQuit));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(PapyrusNotify),			ConsoleRE::StaticFunctionTag, void,	ConsoleRE::BSFixedString>											   ("Notify",	 "PS4", PapyrusNotify));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(PapyrusKernelPrintt),	ConsoleRE::StaticFunctionTag, void, ConsoleRE::BSFixedString>											   ("KernelLog", "PS4", PapyrusKernelPrintt));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(GetUserInput),			ConsoleRE::StaticFunctionTag, ConsoleRE::BSFixedString, ConsoleRE::BSFixedString, ConsoleRE::BSFixedString>("ShowIME",	 "PS4", GetUserInput));
		
		return true;
	}
}