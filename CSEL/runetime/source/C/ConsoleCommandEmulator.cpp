#include "../C/ConsoleCommandEmulator.h"

#include "ConsoleCommands.h"

#include "../../../../OrbisUtil/Third-Party/iwanders/Compile_Time_CRC32/compile_time_crc.hpp"
#include "../../../../OrbisUtil/include/DialogueManger.h"
#include "../../../../OrbisUtil/include/MessageHandler.h"
#include "../../../../OrbisUtil/include/Relocation.h"
#include "../../../../OrbisUtil/include/FileSystem.h"
#include "../../../../OrbisUtil/include/CryptoHandler.h"

#include <atomic>
#include <algorithm>
#include <string>
#include <iostream>

#if defined(__ORBIS__)
#include <kernel.h>
#include <system_service.h>
#elif defined (__OPENORBIS__)
#include <orbis/libkernel.h>
#include <orbis/SystemService.h>
#endif

namespace Runetime
{
	CCE::CCE() :  t_ThreadActive(true), t_Exit(false)
	{ 

	}

	CCE::~CCE() 
	{ 
		this->t_Exit = true;
		this->t_ThreadActive = false;
	}

	bool CCE::InvokeCC(char* command)
	{
		uint32_t Hash = 0;
		if (command)
		{
			std::string CCstring(command);
			std::transform(CCstring.begin(), CCstring.end(), CCstring.begin(), ::tolower);
			const char* str = CCstring.c_str();
			xUtilty::CryptoHandler::GetCRC32(Hash, str);
		}

		switch (Hash)
		{
			// tgm
			case CRC32_STR("tgm"):
				ConsoleCommands::ToggleGodMode();
				break;
			// sgtm
			case CRC32_STR("sgtm"):
				ConsoleCommands::SetGlobalTimeMultiplier();
				break;
			// qqq
			case CRC32_STR("qqq"):
				ConsoleCommands::QuickQuit();
				break;
			// tmm
			case CRC32_STR("tmm"):
				ConsoleCommands::ToggleMapMarkers();
				break;
			// dup
			case CRC32_STR("dup"):
				ConsoleCommands::DumpPapyrusStacks();
				break;
			// DumpPapyrusUpdates
			case CRC32_STR("DumpPapyrusUpdates"):
				ConsoleCommands::DumpPapyrusUpdates();
				break;
			// additem
			case CRC32_STR("additem"):
				ConsoleCommands::PlayerAddItem();
				break;
			case 0xdf07c5e9:
				ConsoleCommands::ADDALL();
				break;
				// teachword
			case CRC32_STR("teachword"):
				ConsoleCommands::teachword();
				break;
			case CRC32_STR("addspell"):
				ConsoleCommands::AddSpell();
				break;
			// ??
			default:
				xUtilty::Notify("Unknown or unsupported command");
				break;
		}

		return true;
	}

	void CCE::ThreadCleanUp()
	{
		scePthreadAttrDestroy(&this->CCEPthreadAttr);
	}

	void* CCEThread(void* arg_a_this)
	{
		CCE* a_this = reinterpret_cast<CCE*>(arg_a_this);
		auto OrbisDialogueManger = xUtilty::DialogueManger::OrbisDialogueManger::GetSingleton();
	
		char buffer[2048] { 0 };
		char msg[512];
		while (true)
		{
			if (a_this->t_Exit)
				break;

			if (Runetime::Hooks::_ScePadDataStorage.PreviousButton == PREV_MAGIC && Runetime::Hooks::_ScePadDataStorage.CurrentButton == CURR_MAGIC)
			{
				OrbisDialogueManger->InitializeImeDialog("Console Command Emulator", "coc qasmoke");
				OrbisDialogueManger->ShowImeDialog(buffer);

				// 0x291960
				sprintf(msg, "Got Console Command '%s'.. do you want to execute this?", buffer);
				xUtilty::DialogueManger::OrbisDialogueManger::GetSingleton()->InitializeMsgDialog(msg, xUtilty::DialogueManger::OrbisDialogueManger::M_USER_MSG, xUtilty::DialogueManger::OrbisDialogueManger::BT_YESNO_FOCUS_NO);
				xUtilty::DialogueManger::OrbisDialogueManger::GetSingleton()->ShowMsgDialog();

				auto ret = xUtilty::DialogueManger::OrbisDialogueManger::GetSingleton()->GetMsgDialogResult()->buttonId;
				xUtilty::KernelPrintOut("ret is %d", ret);

				if (ret == 1)
				{
					a_this->InvokeCC(buffer);
					xUtilty::Notify("🙂");
				}
				else
				{
					xUtilty::Notify("🙁");
				}
			}

			//if (Runetime::Hooks::_ScePadDataStorage.PreviousButton == PREV_EXMAGIC && Runetime::Hooks::_ScePadDataStorage.CurrentButton == CURR_EXMAGIC)
			//	a_this->t_Exit = true;

			sceKernelUsleep(2);
		}
	
		scePthreadExit(NULL);
		a_this->ThreadCleanUp();

		return NULL;
	}

	int32_t CCE::StartCCET()
	{
		int ret = 0;
		struct sched_param param;

		if ((ret = scePthreadAttrInit(&this->CCEPthreadAttr)) != 0)
		{
			xUtilty::Notify("Failed to create CCET Attr...");
			return ret;
		}
		
		scePthreadAttrSetstacksize(&this->CCEPthreadAttr, 0x20000);
		scePthreadAttrSetinheritsched(&this->CCEPthreadAttr, 0);
		scePthreadAttrSetdetachstate(&this->CCEPthreadAttr, 0);
		scePthreadAttrSetaffinity(&this->CCEPthreadAttr, 0x3f);
		
		param.sched_priority = 256; 
		scePthreadAttrSetschedparam(&this->CCEPthreadAttr, &param);
		
		if ((ret = scePthreadCreate(&this->CCEPthread, &this->CCEPthreadAttr, CCEThread, (void*)this, "Console Command Emu Thread")) != 0)
		{
			xUtilty::Notify("Failed to start CCET...");
			return ret;
		}

		return 0;
	}
}