#pragma once

#include "../../../../../../OrbisUtil/include/MessageHandler.h"
#include "../../../../../../OrbisUtil/include/INIHandler.h"
#include "../../../../../../OrbisUtil/include/Mutex.h"
#include "../../../../../../OrbisUtil/include//Logger.h"

#include "../../../../../source/A/ActiveEffect.h"
#include "../../../../../source/B/BSUIMessageData.h"
#include "../../../../../source/M/MapMenu.h"
#include "../../../../../source/G/GFxFunctionHandler.h"
#include "../../../../../source/I/INISettingCollection.h"
#include "../../../../../source/U/UI.h"
#include "../../../../../source/U/UIMenuStrings.h"
#include "../../../../../source/U/UIMessageQueue.h"
#include "../../../../../source/P/PlayerCharacter.h"
#include "../../../../../source/C/ControlMap.h"
#include "../../../../../source/T/TESDataHandler.h"
#include "../../../../../source/P/PlayerControls.h"
#include "../../../../../source/I/InputEvent.h"
#include "../../../../../source/B/ButtonEvent.h"
#include "../../../../../source/B/BSInputDeviceManager.h"
#include "../../../../../source/M/MenuControls.h"
#include "../../../../../source/R/RefHandleUIData.h"
#include "../../../../../source/E/Effect.h"
#include "../../../../../source/E/EffectSetting.h"
#include "../../../../../source/G/GFxMovie.h"
#include "../../../../../source/B/BSTEvent.h"
#include "../../../../../source/T/TESFile.h"
#include "../../../../../source/Misc.h"
#include "../../../../../source/G/GFxMovieRoot.h"

//
//
#include "../../../../../Build/Flags.h"
#include "../../../../../EXTERNAL/SKSE/SKSE.h"

#include "../../ItemData/ItemData.h"

#include <assert.h>
#include <stdexcept>
#include <iostream>
#include <map>
#include <list>

// skyui uses raw keycodes for xinput, do i need to translate them over?
extern const char*		LastControlDown;
extern const char*		LastControlUp;

extern uint32_t			LastKeycodeDown;
extern uint32_t			LastKeycodeUp;
extern uint32_t			ForceContainerCategorization;
extern uint8_t			DisableMapMenuMouseWheel;

extern float			LastX;
extern float			LastY;

typedef std::list<int32_t>							IndexStorageList;
typedef std::map<std::string, IndexStorageList>		IndexStorageTable;

extern IndexStorageTable	s_indexTable;

//
class ScaleFormLog : public ConsoleRE::GFxFunctionHandler
{
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 1);

		const char* msg = a_params.args[0].GetString();
		xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kUserInterfaceLog)->Write(xUtilty::Log::logLevel::kInfo, msg);
	}
};

//
class ScaleFormNotify : public ConsoleRE::GFxFunctionHandler
{
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 1);

		const char* msg = a_params.args[0].GetString();
		xUtilty::Notify("%s", msg);
	}
};

//
class ScaleFormLastKeyCode : public ConsoleRE::GFxFunctionHandler
{
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 1);
		
		bool isKeyDown = a_params.args[0].GetBool();

		if (isKeyDown)
			a_params.retVal->SetNumber(LastKeycodeDown);
		else
			a_params.retVal->SetNumber(LastKeycodeUp);
	}
};

//
class ScaleFormLastControll : public ConsoleRE::GFxFunctionHandler
{
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 1);
		
		bool isKeyDown = a_params.args[0].GetBool();

		if (isKeyDown)
			a_params.retVal->SetString(LastControlDown);
		else
			a_params.retVal->SetString(LastControlUp);
	}
};

//
class ScaleformSetINISetting : public ConsoleRE::GFxFunctionHandler
{
public:
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 2);
		
		const char* settingName = a_params.args[0].GetString();
		double		settingValue = a_params.args[1].GetNumber();

		ConsoleRE::Setting* setting = ConsoleRE::INISettingCollection::GetSingleton()->GetSetting(settingName);

		if (setting)
		{
			auto settingtype = setting->GetType();
			switch (settingtype)
			{
				case ConsoleRE::Setting::Int32:
					setting->SetInt32(settingValue);
					break;
				case ConsoleRE::Setting::Float:
					setting->SetFloat(settingValue);
					break;
				case ConsoleRE::Setting::Bool:
					setting->SetBool(settingValue ? 1 : 0);
					break;
				case ConsoleRE::Setting::Unkown2:
					setting->SetUInt32(((uint32_t)settingValue << 8));
					break;
				case ConsoleRE::Setting::Unkown:
					setting->SetUInt32(settingValue);
					break;
			}
		}
	}
};

//
class ScaleformGetINISetting : public ConsoleRE::GFxFunctionHandler
{
public:
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 1);
		
		const char* settingName = a_params.args[0].GetString();

		ConsoleRE::Setting* setting = ConsoleRE::INISettingCollection::GetSingleton()->GetSetting(settingName);

		a_params.retVal->SetNull();

		if (setting)
		{
			double ret = 0;
			auto settingtype = setting->GetType();
			switch (settingtype)
			{
			case ConsoleRE::Setting::Int32:
				ret = setting->GetInt32();
				break;
			case ConsoleRE::Setting::Float:
				ret = setting->GetFloat();
				break;
			case ConsoleRE::Setting::Bool:
				ret = setting->GetBool() ? 1 : 0;
				break;
			case ConsoleRE::Setting::Unkown2:
				ret = setting->GetUInt32() >> 8;
				break;
			case ConsoleRE::Setting::Unkown:
				ret = setting->GetUInt32();
				break;
			}

			a_params.retVal->SetNumber(ret);
		}
	}
};

//
class ScaleformGetMappedKey : public ConsoleRE::GFxFunctionHandler
{
public:
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 3);
		
		auto eventID		= a_params.args[0].GetString();
		auto DeviceID		= static_cast<uint32_t>(a_params.args[1].GetNumber());
		auto contextID		= static_cast<uint32_t>(a_params.args[2].GetNumber());

		a_params.retVal->SetNull();

		auto controllmapsingleotn = ConsoleRE::ControlMap::GetSingleton();
		if (controllmapsingleotn)
		{
			auto key = controllmapsingleotn->GetMappedKey(eventID, static_cast<ConsoleRE::INPUT_DEVICE>(DeviceID), static_cast<ConsoleRE::UserEvents::INPUT_CONTEXT_ID>(contextID));
			if (key != 0xFF)
			{
				a_params.retVal->SetNumber(static_cast<double>(key));
			}
			else
			{
				a_params.retVal->SetNumber(static_cast<double>(-1));
			}
		}
	}
};

// 
enum MenuType
{
	Open,
	Close,
	Refresh
};

template <MenuType type>
class ScaleformMenu : public ConsoleRE::GFxFunctionHandler
{
public:
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 1);
		
		if constexpr (type == MenuType::Open)
		{
			ConsoleRE::UIMessageQueue::GetSingleton()->AddMessage(a_params.args[0].GetString(), 1, NULL);
		}
		else if constexpr (type == MenuType::Close)
		{
			ConsoleRE::UIMessageQueue::GetSingleton()->AddMessage(a_params.args[0].GetString(), 3, NULL);
		}
		else if constexpr (type == MenuType::Refresh)
		{
			std::logic_error("MenuType::Refresh not supported");
		}
	}
};

//
class ScaleformExtendData : public ConsoleRE::GFxFunctionHandler
{
public:
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 1);
		
		bool val = a_params.args[0].GetBool();
		ItemData::Extend = val;
	}
};

//
class ScaleformExtendAlchemyCategories : public ConsoleRE::GFxFunctionHandler
{
public:
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 1);

		bool bExtend = a_params.args[0].GetBool();
		ItemData::ExtendAlchemyCategories = bExtend;
	}
};

// this is missing code, should be fine enough?
class ScaleformExtendForm : public ConsoleRE::GFxFunctionHandler
{
public:
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 1);

		if (!xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).TryLock())
			return;

		assert(a_params.args[0].GetType() == ConsoleRE::GFxValue::ValueType::kNumber);
		assert(a_params.args[1].GetType() == ConsoleRE::GFxValue::ValueType::kObject);

		uint32_t				formidArg = 0;
		ConsoleRE::TESForm*		formArg = NULL;
		ConsoleRE::GFxValue*	object = NULL;

		bool		bExtra = false;
		bool		bRecursive = false;

		if (a_params.argCount >= 1)
		{
			formidArg = (uint32_t)a_params.args[0].GetNumber();
			if (formidArg > 0)
				formArg = ConsoleRE::TESForm::GetFormFromID(formidArg);
		}

		if (a_params.argCount >= 2)
			object = &a_params.args[1];

		if (a_params.argCount >= 3)
			bExtra = a_params.args[2].GetBool();

		if (a_params.argCount >= 4)
			bRecursive = a_params.args[3].GetBool();

		if (formArg && object)
		{
			ItemData::common(object, reinterpret_cast<ConsoleRE::GFxMovieRoot*>(a_params.movie), formArg);
			if (ItemData::Extend)
			{
				ItemData::Standard(object, reinterpret_cast<ConsoleRE::GFxMovieRoot*>(a_params.movie), formArg, NULL);
				ItemData::magic(object, reinterpret_cast<ConsoleRE::GFxMovieRoot*>(a_params.movie), formArg);
			}
		}

		xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).Unlock();
	}
};

//
enum Mode
{
	Get,
	Set
};

template <Mode Mode>
class ScaleformSEX : public ConsoleRE::GFxFunctionHandler
{
public:
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 1);
		
		if (!xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).TryLock())
			return;

		a_params.retVal->SetNull();

		if constexpr (Mode == Mode::Get)
		{
			using namespace ConsoleRE;
			
			TESNPC* arctorBase = TES_RTTI(PlayerCharacter::GetSingleton()->data.objectReference, TESForm, TESNPC);
			if (arctorBase)
			{
				a_params.retVal->SetNumber(arctorBase->GetSex());
			}
		}
		else if constexpr (Mode == Mode::Set)
		{
			// ConsoleRE::PlayerCharacter::SetPlayerSex();
		}

		xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).Unlock();
	}
};

//
class ScaleformAllowTextInput : public ConsoleRE::GFxFunctionHandler
{
public:
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 1);
		
		bool enable = a_params.args[0].GetBool();
		ConsoleRE::ControlMap* singleton = ConsoleRE::ControlMap::GetSingleton();
		if (singleton)
		{
			singleton->AllowTextInput(enable);
		}
	}
};

//
class ScaleformShowOnMap : public ConsoleRE::GFxFunctionHandler
{
public:
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 1);
		
		if (!xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).TryLock())
		{
			return;
		}
		
		int32_t index	= a_params.args[0].GetNumber();
		auto UI			= ConsoleRE::UI::GetSingleton();
		auto UIMS       = ConsoleRE::UIMenuStrings::GetSingleton();
		auto UIMQ		= ConsoleRE::UIMessageQueue::GetSingleton();

		if (index >= 0 && UI->IsMenuOpen(UIMS->mapMenu))
		{
			auto menu = UI->menuMap.findT(UIMS->mapMenu);
			ConsoleRE::MapMenu* mapmenu = static_cast<ConsoleRE::MapMenu*>(menu ? menu->menu.get() : NULL);

			if (mapmenu && index < mapmenu->Unk30910.size())
			{
				auto& marker	= mapmenu->Unk30910[index];
				uint32_t handle = marker.Unk08;
				if (handle)
				{
					ConsoleRE::RefHandleUIData* msgdata = static_cast<ConsoleRE::RefHandleUIData*>(ConsoleRE::CreateUIMessageData(UIMS->refHandleUIData));
					if (msgdata)
					{
						msgdata->refHandle = handle;
						UIMQ->AddMessage(UIMS->mapMenu, 0, msgdata);
					}
				}
			}
		}

		xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).Unlock();
	}
};

//
class ScaleformSendModEvent : public ConsoleRE::GFxFunctionHandler
{
public:
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 1);
		
		if (!xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).TryLock())
			return;

		const char*	  eventName = a_params.args[0].GetString();
		const char*	  strArg = NULL;
		float		  numArg = 0.0;
		uint32_t	  formidArg = 0;
		ConsoleRE::TESForm*	  formArg = NULL;

		if (a_params.argCount >= 2)
			strArg = a_params.args[1].GetString();

		if (a_params.argCount >= 3)
			numArg = a_params.args[2].GetNumber();

		if (a_params.argCount >= 4) 
		{
			formidArg = (uint32_t)a_params.args[3].GetNumber();
			if (formidArg > 0)
				formArg = ConsoleRE::TESForm::GetFormFromID(formidArg);
		}

		ConsoleRE::BSFixedString aEventName(eventName);
		ConsoleRE::BSFixedString aStrArg(strArg);

#if USE_SKSE_ADDON
		SKSE::ModCallbackEvent evn(aEventName, aStrArg, numArg, formArg);
		SKSE::ModCallbackEventDispatcher::GetSingleton()->SendEventSink(&evn);
#endif

		xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).Unlock();
	}
};

//
class ScaleformStoreIndices : public ConsoleRE::GFxFunctionHandler
{
public:
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 2);
		assert(a_params.args[0].GetType() == ConsoleRE::GFxValue::ValueType::kString);
		assert(a_params.args[1].GetType() == ConsoleRE::GFxValue::ValueType::kArray);
		

		if (!xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).TryLock())
			return;
		
		std::string key(a_params.args[0].GetString());
		ConsoleRE::GFxValue * indices = &a_params.args[1];

		s_indexTable[key].clear();

		for (uint32_t i = 0; i<indices->GetArraySize(); i++)
		{
			ConsoleRE::GFxValue t;
			if (indices->GetElement(i, &t))
			{
				if (t.GetType() == ConsoleRE::GFxValue::ValueType::kNumber)
				{
					s_indexTable[key].push_back(t.GetNumber());
				}

			}
		}

		xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).Unlock();

	}
};

//
class ScaleformLoadIndices : public ConsoleRE::GFxFunctionHandler
{
public:
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 2);
		assert(a_params.args[0].GetType() == ConsoleRE::GFxValue::ValueType::kString);
		assert(a_params.args[1].GetType() == ConsoleRE::GFxValue::ValueType::kArray);
		
		if (!xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).TryLock())
			return;

		std::string key(a_params.args[0].GetString());
		ConsoleRE::GFxValue * indicesOut = &a_params.args[1];

		IndexStorageTable::iterator indices = s_indexTable.find(key);

		if (indices != s_indexTable.end())
		{
			for (IndexStorageList::iterator iter = indices->second.begin(); iter != indices->second.end(); ++iter)
			{
				ConsoleRE::GFxValue t;
				t.SetNumber(*iter);
				indicesOut->PushBack(t);
			}
		}

		// GlobalMutex5
		xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).Unlock();
	}
};

//
class ScaleformGetModList : public ConsoleRE::GFxFunctionHandler
{
public:
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 1);
		
		if (!xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).TryLock())
			return;

		ConsoleRE::TESDataHandler* data = ConsoleRE::TESDataHandler::GetSingleton();

		a_params.movie->CreateArray(a_params.retVal);

		for (int i = 0; i < data->Unk918.size(); i++)
		{
			ConsoleRE::TESFile* mod = data->Unk918[i];
			if (mod)
			{
				ConsoleRE::GFxValue info;
				a_params.movie->CreateObject(&info);

				info.RegisterNumber("index",	   i);
				info.RegisterString("name",        mod->fileName);
				info.RegisterString("author",      mod->Creator.c_str());
				info.RegisterString("description", mod->Summary.c_str());
				
				a_params.retVal->PushBack(info);
			}
		}

		xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).Unlock();
	}
};

//
class ScaleformForceContainerCategorization : public ConsoleRE::GFxFunctionHandler
{
public:
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 1);

		bool enable = a_params.args[0].GetBool();

		ForceContainerCategorization = enable ? 1 : 0;
	}
};

//
class ScaleformEnableMapMenuMouseWheel : public ConsoleRE::GFxFunctionHandler
{
public:
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 1);

		if (!xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).TryLock())
			return;
		
		bool enable = a_params.args[0].GetBool();
		DisableMapMenuMouseWheel = enable ? 1 : 0;

		xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).Unlock();
	}
};

//
class ScaleformStartRemapMode : public ConsoleRE::GFxFunctionHandler
{
public:
	class RemapHandler : public ConsoleRE::BSTEventSink<ConsoleRE::InputEvent*>
	{
	public:
		RemapHandler(ConsoleRE::GFxValue& a_GFxvalue) :
			scope(a_GFxvalue)
		{}

		~RemapHandler() override = default;

		ConsoleRE::BSEventNotifyControl ProcessEvent(ConsoleRE::InputEvent* const* a_event, ConsoleRE::BSTEventSource<ConsoleRE::InputEvent*>* a_source) override
		{
			const ConsoleRE::ButtonEvent* e = static_cast<const ConsoleRE::ButtonEvent*>(*a_event);

			// Make sure this is really a button event
			if (!e || e->eventType != ConsoleRE::INPUT_EVENT_TYPE::kButton)
			{
				return ConsoleRE::BSEventNotifyControl::kContinue;
			}

			// PAD_BUTTON_CROSS
			if (e->idCode == 0x00004000)
			{
				return ConsoleRE::BSEventNotifyControl::kContinue;
			}

#if _DEBUG
			PRINT_FMT("Keycode: 0x%lx", e->idCode);
#elif NDEBUG
			xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kDebug, "RemapHandler Got Keycode: 0x%lx", e->idCode);
#endif

			//
			ConsoleRE::GFxValue arg(e->idCode);
			scope.Invoke("EndRemapMode", NULL, &arg, 1);

			//
			ConsoleRE::MenuControls::GetSingleton()->remapMode = false;
			ConsoleRE::PlayerControls::GetSingleton()->data.remapMode = false;

			//
			a_source->RemoveEventSink(this);

			//
			delete this;

			//
			return ConsoleRE::BSEventNotifyControl::kContinue;
		}
	public:
		ConsoleRE::GFxValue scope;
	};
public:
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 1);

		ConsoleRE::PlayerControls* playerControls = ConsoleRE::PlayerControls::GetSingleton();
		if (!playerControls)
			return;

		ConsoleRE::MenuControls	* menuControls = ConsoleRE::MenuControls::GetSingleton();
		if (!menuControls)
			return;

		ConsoleRE::BSInputDeviceManager* pInputEventDispatcher = ConsoleRE::BSInputDeviceManager::GetSingleton();
		if (!(pInputEventDispatcher))
			return;

		pInputEventDispatcher->AddEventSink(new RemapHandler(a_params.args[0]));

		menuControls->remapMode = true;
		playerControls->data.remapMode = true;
	}
};

//
class ScaleformRequestActivePlayerEffects : public ConsoleRE::GFxFunctionHandler
{
	class ActiveEffectVisitor
	{
		ConsoleRE::GFxMovie* movieView;
		ConsoleRE::GFxValue* activeEffects;

	public:
		ActiveEffectVisitor(ConsoleRE::GFxMovie* a_movieView, ConsoleRE::GFxValue* a_activeEffects)
			: movieView(a_movieView), activeEffects(a_activeEffects) {}

		bool Accept(ConsoleRE::ActiveEffect * e)
		{
			if (!e)
				return false;

			if (e->duration <= 0)
				return true;

			if (e->effect == NULL || e->effect->baseEffect == NULL)
				return true;

			ConsoleRE::EffectSetting * mgef = e->effect->baseEffect;

			// Skip effect if condition wasn't evaluated to true or HideInUI flag is set
			if (e->flags & 0x8000 || mgef->data.flags & 0x00008000)
				return true;

			ConsoleRE::GFxValue obj;
			movieView->CreateObject(&obj);

			obj.RegisterNumber("duration",		e->duration);
			obj.RegisterNumber("elapsed",		e->elapsedSeconds);
			obj.RegisterNumber("magnitude",		e->magnitude);

			obj.RegisterNumber("effectFlags",	mgef->data.flags);
			obj.RegisterNumber("subType",	    mgef->data.associatedSkill);
			obj.RegisterNumber("archetype",     mgef->data.archetype);
			obj.RegisterNumber("actorValue",    mgef->data.primaryAV);
			obj.RegisterNumber("magicType",     mgef->data.resistVariable);
			
			obj.RegisterNumber("id",			(uint64_t)e);

			activeEffects->PushBack(obj);
			return true;
		}
	};
public:
	void Call(Params& a_params) override
	{
		assert(a_params.argCount >= 1);
		assert(a_params.args[0].GetType() == ConsoleRE::GFxValue::ValueType::kArray);
	
		if (!xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).TryLock())
		{
			PRINT_POS;
			return;
		}

		ConsoleRE::BSSimpleList<ConsoleRE::ActiveEffect*>* effects = ConsoleRE::PlayerCharacter::GetSingleton()->GetActiveEffectList();
		if (effects)
		{
			ActiveEffectVisitor v(a_params.movie, &a_params.args[0]);
			effects->Visit(v);
		}

		xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).Unlock();
	}
};

//
class ScaleformRequestActorValues : public ConsoleRE::GFxFunctionHandler
{
public:
	void Call(Params& a_params) override
	{
		using namespace ConsoleRE;

		assert(a_params.argCount >= 1);

		if (!xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).TryLock())
		{
			return;
		}

		assert(a_params.args[0].GetType() == ConsoleRE::GFxValue::ValueType::kNumber);
		assert(a_params.args[1].GetType() == ConsoleRE::GFxValue::ValueType::kArray);
		assert(a_params.args[2].GetType() == ConsoleRE::GFxValue::ValueType::kArray);

		uint32_t				formidArg = 0;
		ConsoleRE::TESForm*		formArg = 0;
		ConsoleRE::GFxValue*	inArray = NULL;
		ConsoleRE::GFxValue*	outArray = NULL;

		if (a_params.argCount >= 1)
		{
			formidArg = (uint32_t)a_params.args[0].GetNumber();
			if (formidArg > 0)
			{
				formArg = ConsoleRE::TESForm::GetFormFromID(formidArg);
			}
		}
		
		if (!formArg)
		{
			xUtilty::Notify("ScaleformRequestActorValues - Invalid form (%X)", formidArg);
			xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).Unlock();
			return;
		}

		ConsoleRE::Actor* actor = TES_RTTI(formArg, TESForm, Actor);
		if (!actor)
		{
			xUtilty::Notify("Scaleform_RequestActorValues - Invalid form type (%X)", formidArg);
			xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).Unlock();
			return;
		}

		if (a_params.argCount >= 2)
		{
			inArray = &a_params.args[1];
		}

		if (a_params.argCount >= 3) 
		{
			outArray = &a_params.args[2];
		}

		ConsoleRE::GFxValue val;
		uint32_t size = inArray->GetArraySize();
		for (uint32_t i = 0; i < size; i++)
		{
			inArray->GetElement(i, &val);
			if (val.GetType() != ConsoleRE::GFxValue::ValueType::kNumber)
				continue;

			ConsoleRE::GFxValue avOut;
			a_params.movie->CreateObject(&avOut);

			uint32_t actorValue = val.GetNumber();
			avOut.RegisterNumber("id",		actorValue);
			avOut.RegisterNumber("base",    actor->GetBaseActorValue(actorValue));
			avOut.RegisterNumber("current", actor->GetActorValue(actorValue));
			avOut.RegisterNumber("maximum", actor->GetPermanentActorValue(actorValue));

			outArray->PushBack(avOut);
		}

		xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).Unlock();
	}
};
