#include "../../../MessageQueueUI/MessageQueue.h"

#include "../../../../../../source/A/Array.h"
#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/C/ControlMap.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/U/UI.h"
#include "../../../../../../source/T/TESForm.h"
#include "../../../../../../source/U/UIMessageQueue.h"

//
#include "../../../../../../source/P/PackUnpackImpl.h"

#include "../../../../../Internal/Tasks/Tasks/TaskUIInvoke.h"
#include "../../../../../Internal/Tasks/Tasks/TaskUIInvokeForm.h"

#include "../UI/Custom_Menu.h"
#include "../UI/PapyrusExtUI.h"

namespace PapyrusExtUI
{
	// I really hate doing this...
	using namespace ConsoleRE;

	bool		  UIGetBool(StaticFunctionTag* tag, BSFixedString str1, BSFixedString str2)
	{
#if _DEBUG
		PRINT_FMT("%p %s %s", tag, str1.m_data, str2.m_data);
#endif

		auto m = ConsoleRE::UI::GetSingleton()->menuMap.findT(str1);
		if (m)
		{
			GFxValue ret;
			if (m && m->menu && m->menu->uiMovie && m->menu->uiMovie->GetVariable(&ret, str2.m_data))
			{
				if (ret.GetType() == GFxValue::ValueType::kBoolean)
				{
					return ret.GetBool();
				}
			}
		}

		return false;
	}

	uint32_t	  UIGetUINT(StaticFunctionTag* tag, BSFixedString str1, BSFixedString str2)
	{
#if _DEBUG
		PRINT_FMT("%p %s %s", tag, str1.m_data, str2.m_data);
#endif
		auto m = ConsoleRE::UI::GetSingleton()->menuMap.findT(str1);
		if (m)
		{
			GFxValue ret;
			if (m && m->menu && m->menu->uiMovie && m->menu->uiMovie->GetVariable(&ret, str2.m_data))
			{
				if (ret.GetType() == GFxValue::ValueType::kNumber)
				{
					return ret.GetNumber();
				}
			}
		}

		return 0;
	}

	float		  UIGetFloat(StaticFunctionTag* tag, BSFixedString str1, BSFixedString str2)
	{
#if _DEBUG
		PRINT_FMT("%p %s %s", tag, str1.m_data, str2.m_data);
#endif
		auto m = ConsoleRE::UI::GetSingleton()->menuMap.findT(str1);
		if (m)
		{
			GFxValue ret;
			if (m && m->menu && m->menu->uiMovie && m->menu->uiMovie->GetVariable(&ret, str2.m_data))
			{
				if (ret.GetType() == GFxValue::ValueType::kNumber)
				{
					return ret.GetNumber();
				}
			}
		}

		return 0;
	}

	BSFixedString UIGetString(StaticFunctionTag* tag, BSFixedString str1, BSFixedString str2)
	{
#if _DEBUG
		PRINT_FMT("%p %s %s", tag, str1.m_data, str2.m_data);
#endif
		auto m = ConsoleRE::UI::GetSingleton()->menuMap.findT(str1);
		if (m)
		{
			GFxValue ret;
			if (m->menu && m->menu->uiMovie && m->menu->uiMovie->GetVariable(&ret, str2.m_data))
			{
				if (ret.GetType() == GFxValue::ValueType::kString)
				{
					return BSFixedString(ret.GetString());
				}
			}
		}

		return BSFixedString();
	}

	void		  UISetBool(StaticFunctionTag* tag, BSFixedString str1, BSFixedString str2, bool val)
	{
#if _DEBUG
		PRINT_FMT("%p %s %s %d", tag, str1.m_data, str2.m_data, val);
#endif
		auto m = ConsoleRE::UI::GetSingleton()->menuMap.findT(str1);
		if (m && m->menu && m->menu->uiMovie)
		{
			GFxValue set(val);
			m->menu->uiMovie->SetVariable(str2.m_data, set);
		}
	}

	void		  UISetUINT(StaticFunctionTag* tag, BSFixedString str1, BSFixedString str2, uint32_t val)
	{
#if _DEBUG
		PRINT_FMT("%p %s %s %d", tag, str1.m_data, str2.m_data, val);
#endif
		auto m = ConsoleRE::UI::GetSingleton()->menuMap.findT(str1);
		if (m && m->menu && m->menu->uiMovie)
		{
			GFxValue set(val);
			m->menu->uiMovie->SetVariable(str2.m_data, set);
		}

		return;
	}

	void		  UISetFloat(StaticFunctionTag* tag, BSFixedString str1, BSFixedString str2, float val)
	{
#if _DEBUG
		PRINT_FMT("%p %s %s %f", tag, str1.m_data, str2.m_data, val);
#endif
		auto m = ConsoleRE::UI::GetSingleton()->menuMap.findT(str1);
		if (m && m->menu && m->menu->uiMovie)
		{
			GFxValue set(val);
			m->menu->uiMovie->SetVariable(str2.m_data, set);
		}
		return;
	}

	void		  UISetString(StaticFunctionTag* tag, BSFixedString str1, BSFixedString str2, BSFixedString str3)
	{
#if _DEBUG
		PRINT_FMT("%p %s %s %s", tag, str1.m_data, str2.m_data, str3.m_data);
#endif
		auto m = ConsoleRE::UI::GetSingleton()->menuMap.findT(str1);
		if (m && m->menu && m->menu->uiMovie)
		{
			GFxValue set(str3.m_data);
			m->menu->uiMovie->SetVariable(str2.m_data, set);
		}

		return;
	}

	void		  UIInvokeBool(StaticFunctionTag* tag, BSFixedString str1, BSFixedString str2, bool val)
	{
#if _DEBUG
		PRINT_FMT("%p %s %s %d", tag, str1.m_data, str2.m_data, val);
#endif
		// Create task
		auto item = new Tasks::TaskUIInvoke(str1, str2);
		item->m_args.resize(1);
		item->m_args[0].SetNumber(val);
		//

		// push into the queue.
		MessageQueue::UI::PushQueue(item);
	}

	void		  UIInvokeFloat(StaticFunctionTag* tag, BSFixedString str1, BSFixedString str2, float val)
	{
#if _DEBUG
		PRINT_FMT("%p %s %s %f", tag, str1.m_data, str2.m_data, val);
#endif
		// Create task
		auto item = new Tasks::TaskUIInvoke(str1, str2);
		item->m_args.resize(1);
		item->m_args[0].SetNumber(val);
		//

		// push into the queue.
		MessageQueue::UI::PushQueue(item);
	}

	void		  UIInvokeUINT(StaticFunctionTag* tag, BSFixedString str1, BSFixedString str2, uint32_t val)
	{
#if _DEBUG
		PRINT_FMT("%p %s %s %d", tag, str1.m_data, str2.m_data, val);
#endif
		// Create task
		auto item = new Tasks::TaskUIInvoke(str1, str2);
		item->m_args.resize(1);
		item->m_args[0].SetNumber(val);
		//

		// push into the queue.
		MessageQueue::UI::PushQueue(item);
	}

	void		  UIInvokeString(StaticFunctionTag* tag, BSFixedString str1, BSFixedString str2, BSFixedString str3)
	{
#if _DEBUG
		PRINT_FMT("%p %s %s %s", tag, str1.m_data, str2.m_data, str3.m_data);
#endif
		// Create task
		auto item = new Tasks::TaskUIInvoke(str1, str2);
		item->m_args.resize(1);
		item->m_args[0].SetString(str3.m_data);
		//

		// push into the queue.
		MessageQueue::UI::PushQueue(item);
	}

	bool		  UIOpen(StaticFunctionTag* tag, BSFixedString name)
	{	
#if _DEBUG
		PRINT_FMT("%p %s", tag, name.m_data);
#endif
		if (name.m_data)
		{
			return UI::GetSingleton()->IsMenuOpen(name);
		}

		return false;
	}

	bool		  UITextInputEnabled(StaticFunctionTag* tag)
	{
#if _DEBUG
		PRINT_FMT("%p", tag);
#endif
		auto Singleton = ConsoleRE::ControlMap::GetSingleton();
		if (Singleton)
		{
			return Singleton->enabledControls != 0;
		}

		return false;
	}

	void		  OpenMenu(StaticFunctionTag* tag, BSFixedString swf, int32_t flag)
	{
#if _DEBUG
		PRINT_FMT("%p %s %d", tag, swf.m_data, flag);
#endif
		CustomMenu::CustomMenu::SetSWF(swf.m_data);
		UIMessageQueue::GetSingleton()->AddMessage("CustomMenu", 1, nullptr);
	}

	void		  CloseMenu(StaticFunctionTag* tag)
	{
#if _DEBUG
		PRINT_FMT("%p", tag);
#endif
		UIMessageQueue::GetSingleton()->AddMessage("CustomMenu", 3, nullptr);
	}

	void		  InvokeForm(StaticFunctionTag* tag, BSFixedString menuName, BSFixedString targetStr, TESForm* form)
	{
#if _DEBUG
		PRINT_FMT("%p %s %s %p", tag, menuName.m_data, targetStr.m_data, form);
#endif
		if (!form || !menuName.m_data || !targetStr.m_data)
			return;

		// Create task
		auto command = new Tasks::TaskUIInvokeForm(menuName, targetStr, (uint64_t)form, form->FormType);
		
		// Push to queue
		MessageQueue::UI::PushQueue(command);
	}
	
	void		  InvokeStringA(StaticFunctionTag* tag, BSFixedString menuName, BSFixedString targetStr, std::vector<BSFixedString> args)
	{
		if (!menuName.m_data || !targetStr.m_data)
			return;

		auto len = args.size();
		auto command = new Tasks::TaskUIInvoke(menuName, targetStr);
		command->m_args.resize(len);

		for (int i = 0; i < len; i++)
		{
#if _DEBUG
			PRINT_FMT("%p %s %s %s", tag, menuName.m_data, targetStr.m_data, args[i].m_data);
#endif

			command->m_args[i].SetString(args[i].m_data);
		}

		MessageQueue::UI::PushQueue(command);
	}

	void		  InvokeBoolA(StaticFunctionTag* tag, BSFixedString menuName, BSFixedString targetStr, std::vector <bool> args)
	{
		if (!menuName.m_data || !targetStr.m_data)
			return;

		auto len = args.size();
		auto command = new Tasks::TaskUIInvoke(menuName, targetStr);
		command->m_args.resize(len);

		for (int i = 0; i < len; i++)
		{
#if _DEBUG
			PRINT_FMT("%p %s %s %d", tag, menuName.m_data, targetStr.m_data, args[i]);
#endif
			command->m_args[i].SetBoolean(static_cast<bool>(args[i]));
		}

		MessageQueue::UI::PushQueue(command);
	}

	void		  InvokeIntA(StaticFunctionTag* tag, BSFixedString menuName, BSFixedString targetStr, std::vector<int> args)
	{
		if (!menuName.m_data || !targetStr.m_data)
			return;

		auto len = args.size();
		auto command = new Tasks::TaskUIInvoke(menuName, targetStr);
		command->m_args.resize(len);

		for (int i = 0; i < len; i++)
		{
#if _DEBUG
			PRINT_FMT("%p %s %s %d", tag, menuName.m_data, targetStr.m_data, args[i]);
#endif
			command->m_args[i].SetNumber(args[i]);
		}

		MessageQueue::UI::PushQueue(command);
	}

	void		  InvokeFloatA(StaticFunctionTag* tag, BSFixedString menuName, BSFixedString targetStr, std::vector<float> args)
	{
		if (!menuName.m_data || !targetStr.m_data)
			return;

		auto len = args.size();
		auto command = new Tasks::TaskUIInvoke(menuName, targetStr);
		command->m_args.resize(len);

		for (int i = 0; i < len; i++)
		{
#if _DEBUG
			PRINT_FMT("%p %s %s %f", tag, menuName.m_data, targetStr.m_data, args[i]);
#endif
			command->m_args[i].SetNumber(args[i]);
		}

		MessageQueue::UI::PushQueue(command);
	}

	bool		  RegisterUI(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		ConsoleRE::UI::GetSingleton()->Register("CustomMenu", CustomMenu::CustomMenu::Create);

		//
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(InvokeStringA),	StaticFunctionTag, void, BSFixedString, BSFixedString, std::vector<BSFixedString>>		("InvokeStringA",		"UI", InvokeStringA));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(InvokeBoolA),		StaticFunctionTag, void, BSFixedString, BSFixedString, std::vector<bool>>				("InvokeBoolA",			"UI", InvokeBoolA));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(InvokeIntA),		StaticFunctionTag, void, BSFixedString, BSFixedString, std::vector<int>>				("InvokeIntA",			"UI", InvokeIntA));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(InvokeFloatA),		StaticFunctionTag, void, BSFixedString, BSFixedString, std::vector<float>>				("InvokeFloatA",		"UI", InvokeFloatA));
		//

		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(CloseMenu),			StaticFunctionTag, void>															("CloseCustomMenu",		"UI", CloseMenu));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UITextInputEnabled),  StaticFunctionTag, bool>															("IsTextInputEnabled",	"UI", UITextInputEnabled));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UIOpen),			    StaticFunctionTag, bool,		        BSFixedString>								("IsMenuOpen",			"UI", UIOpen));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(OpenMenu),			StaticFunctionTag, void,		        BSFixedString, int32_t>						("OpenCustomMenu",		"UI", OpenMenu));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UIGetBool),			StaticFunctionTag, bool,		        BSFixedString, BSFixedString>				("GetBool",				"UI", UIGetBool));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UIGetUINT),			StaticFunctionTag, uint32_t,	        BSFixedString, BSFixedString>				("GetInt",				"UI", UIGetUINT));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UIGetFloat),			StaticFunctionTag, float,		        BSFixedString, BSFixedString>				("GetFloat",			"UI", UIGetFloat));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UIGetString),			StaticFunctionTag, BSFixedString,       BSFixedString, BSFixedString>				("GetString",			"UI", UIGetString));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UISetBool),			StaticFunctionTag, void, BSFixedString, BSFixedString, bool>						("SetBool",				"UI", UISetBool));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UISetUINT),			StaticFunctionTag, void, BSFixedString, BSFixedString, uint32_t>					("SetInt",				"UI", UISetUINT));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UISetFloat),			StaticFunctionTag, void, BSFixedString, BSFixedString, float>						("SetFloat",			"UI", UISetFloat));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UISetString),			StaticFunctionTag, void, BSFixedString, BSFixedString, BSFixedString>				("SetString",			"UI", UISetString));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UIInvokeBool),		StaticFunctionTag, void, BSFixedString, BSFixedString, bool>						("InvokeBool",			"UI", UIInvokeBool));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UIInvokeFloat),		StaticFunctionTag, void, BSFixedString, BSFixedString, float>						("InvokeFloat",			"UI", UIInvokeFloat));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UIInvokeUINT),		StaticFunctionTag, void, BSFixedString, BSFixedString, uint32_t>					("InvokeInt",			"UI", UIInvokeUINT));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(UIInvokeString),		StaticFunctionTag, void, BSFixedString, BSFixedString, BSFixedString>				("InvokeString",		"UI", UIInvokeString));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(InvokeForm),			StaticFunctionTag, void, BSFixedString, BSFixedString, TESForm*>					("InvokeForm",		    "UI", InvokeForm));

		VM->SetCallableFromTasklets("UI", "InvokeStringA",			true);
		VM->SetCallableFromTasklets("UI", "InvokeBoolA",			true);
		VM->SetCallableFromTasklets("UI", "InvokeIntA",				true);
		VM->SetCallableFromTasklets("UI", "InvokeFloatA",			true);
		VM->SetCallableFromTasklets("UI", "InvokeBool",				true);
		VM->SetCallableFromTasklets("UI", "InvokeInt",				true);
		VM->SetCallableFromTasklets("UI", "InvokeFloat",			true);
		VM->SetCallableFromTasklets("UI", "InvokeString",			true);
		VM->SetCallableFromTasklets("UI", "InvokeForm",				true);
		VM->SetCallableFromTasklets("UI", "IsTextInputEnabled",		true);
		VM->SetCallableFromTasklets("UI", "OpenCustomMenu",			true);
		VM->SetCallableFromTasklets("UI", "CloseCustomMenu",		true);

		return true;
	}
}