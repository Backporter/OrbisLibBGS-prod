#include "../TESForm/PapyrusExtTESForm.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESForm.h"
#include "../../../../../../source/A/AlchemyItem.h"
#include "../../../../../../source/B/BGSKeyword.h"
#include "../../../../../../source/B/BGSTextureSet.h"
#include "../../../../../../source/P/PackUnpackImpl.h"

#include "../../../../../../../OrbisUtil/include/INIHandler.h"

#include "../../../../../../Build/Flags.h"
#include "../../../../../../EXTERNAL/SKSE/SKSE.h"

namespace PapyrusExtTESForm
{
	// I really hate doing this...
	using namespace ConsoleRE;

#pragma region
	std::vector<BGSKeyword*> GetKeywords(TESForm* thisForm)
	{
		std::vector<BGSKeyword*> ret;
		if (!thisForm)
		{
			return ret;
		}

		BGSKeywordForm* pKeywords = thisForm->Cast2KeywordForm();
		if (pKeywords)
		{
			for (uint32_t i = 0; i < pKeywords->numKeywords; i++)
			{
				if (pKeywords->keywords[i])
					ret.push_back(pKeywords->keywords[i]);
			}
		}
		return ret;
	}
#pragma endregion

	uint32_t      GetFormType(TESForm* Form)
	{
		if (Form)
		{
			return Form->FormType;
		}

		return 0;	
	}

	BSFixedString GetFormName(TESForm* Form)
	{
		if (Form)
		{
			auto FullForm = Form->Cast2FullForm();
			if (FullForm)
			{
				return FullForm->name.m_data;
			}
		}

		return NULL;
	}

	float         GetFormWeight(TESForm* Form)
	{
		if (Form)
		{
			auto WeightForm = Form->Cast2WeightForm();
			if (WeightForm)
			{
				return WeightForm->weight;
			}
		}

		return 0.0f;
	}

	uint32_t	  GetFormKeywordsCount(TESForm* Form)
	{
		if (Form)
		{
			auto KeywordForm = Form->Cast2KeywordForm();
			if (KeywordForm)
			{
				return KeywordForm->numKeywords;
			}
		}

		return 0;
	}

	bool          FormIsPlayable(TESForm* Form)
	{
		if (Form)
		{
			return (Form->formFlags & 4) == 0;
		}

		return false;
	}

	bool		  FormHasModel(TESForm* Form)
	{
		if (Form)
		{
			auto model = Form->Cast2ModelForm();
			if (model)
			{
				return true;
			}
		}

		return false;
	}

	BSFixedString GetFormModel(TESForm* Form)
	{
		if (Form)
		{
			auto ModelForm = Form->Cast2ModelForm();
			if (ModelForm)
			{
				return ModelForm->model;
			}
		}

		return NULL;
	}

	uint32_t	  GetFormTextureCount(TESForm* Form)
	{
		if (Form)
		{
			auto TexturSwapForm = Form->Cast2TextureSwapForm();
			if (TexturSwapForm)
			{
				return TexturSwapForm->numAlternateTextures;
			}
		}

		return 0;
	}

	void          SetFormName(TESForm* Form, BSFixedString string)
	{
		if (Form)
		{
			auto FullForm = Form->Cast2FullForm();
			if (FullForm)
			{
				FullForm->name.m_data = string.m_data;
			}
		}
	}

	void          SetFormWeight(TESForm* Form, float value)
	{
		if (Form)
		{
			auto WeightForm = Form->Cast2WeightForm();
			if (WeightForm)
			{
				WeightForm->weight = value;
			}
		}
	}

	void		  SetFormValue(TESForm* Form, uint32_t Value)
	{
		if (Form)
		{
			auto ValueForm = Form->Cast2ValueForm();
			if (ValueForm)
			{
				ValueForm->value = Value;
			}
		}
	}

	BGSKeyword*	  GetFormKeywords(TESForm* Form, uint32_t i)
	{
		if (Form)
		{
			auto KeywordForm = Form->Cast2KeywordForm();
			if (KeywordForm)
			{
				if (i < KeywordForm->numKeywords)
				{
					return KeywordForm->keywords[i];
				}
			}
		}

		return NULL;
	}

	void		  SetFormKnown(TESForm* Form, bool knows)
	{
		if (Form)
		{
			if (knows)
			{
				Form->formFlags |= 64;
			}
			else
			{
				Form->formFlags &= 64;
			}
		}
	}

	void		  SetFormModel(TESForm* Form, BSFixedString newpath)
	{
		if (Form)
		{
			auto ModelForm = Form->Cast2ModelForm();
			if (ModelForm)
			{
				ModelForm->SetModel(newpath.m_data);
			}
		}
	}
	
	BGSTextureSet* GetFormTextureSet(TESForm* Form, uint32_t i)
	{
		if (Form)
		{
			auto TextreForm = Form->Cast2TextureSwapForm();
			if (TextreForm)
			{
				if (TextreForm->alternateTextures && i <= TextreForm->numAlternateTextures)
				{
					return TextreForm->alternateTextures[i].textureSet;
				}
			}
		}

		return NULL;
	}

	void		   SetFormModelTexture(TESForm* Form, BGSTextureSet* TextureSet, uint32_t i)
	{
		if (Form)
		{
			TESModelTextureSwap* texswap = TES_RTTI(Form, TESForm, TESModelTextureSwap);
			if (texswap)
			{
				if (texswap->alternateTextures)
				{
					if (i < texswap->numAlternateTextures)
					{
						texswap->alternateTextures[i].textureSet = TextureSet;
					}
				}
			}
		}
	}

	uint32_t       GetFormValue(TESForm* Form)
	{
		int value = 0;
		if (Form)
		{
			if (Form->FormType == ConsoleRE::AlchemyItem::TypeID)
			{
				auto Item = Form->Cast2AlchemyItem();
				if (Item)
				{
					value = Item->data.costOverride;
				}
			}
			else
			{
				auto ValueForm = Form->Cast2ValueForm();
				if (ValueForm)
				{
					value = ValueForm->value;
				}
			}
		}
		return value;
	}

	//
	void RegisterForKey(TESForm * thisForm, uint32_t a_key)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::InputKeyEventRegistrationMapHolder::GetSingleton()->Register<TESForm>(a_key, thisForm->FormType, thisForm);
#endif
	}

	void UnregisterForKey(TESForm * thisForm, uint32_t a_key)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::InputKeyEventRegistrationMapHolder::GetSingleton()->Unregister<TESForm>(a_key, thisForm->FormType, thisForm);
#endif
	}

	void UnregisterForAllKeys(TESForm * thisForm)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::InputKeyEventRegistrationMapHolder::GetSingleton()->UnregisterAll<TESForm>(thisForm->FormType, thisForm);
#endif
	}

	void RegisterForControl(TESForm * thisForm, BSFixedString control)
	{
		if (!thisForm)
			return;

		// PRINT_FMT("%p %s", thisForm, control.c_str());

#if USE_SKSE_ADDON
		SKSE::InputControlRegistrationMapHolder::GetSingletion()->Register<TESForm>(control, thisForm->FormType, thisForm);
#endif
	}

	void UnregisterForControl(TESForm * thisForm, BSFixedString control)
	{
		if (!thisForm)
			return;

		// PRINT_FMT("%p %s", thisForm, control.c_str());

#if USE_SKSE_ADDON
		SKSE::InputControlRegistrationMapHolder::GetSingletion()->Unregister<TESForm>(control, thisForm->FormType, thisForm);
#endif
	}

	void UnregisterForAllControls(TESForm * thisForm)
	{
		if (!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::InputControlRegistrationMapHolder::GetSingletion()->UnregisterAll<TESForm>(thisForm->FormType, thisForm);
#endif
	}

	void RegisterForMenu(TESForm * base, BSFixedString menuName)
	{
		if (!base || !menuName.m_data)
			return;

		// PRINT_FMT("%p %s", base, menuName.c_str());

#if USE_SKSE_ADDON
		SKSE::MenuOpenCloseRegistrationMapHolder::GetSingleton()->Register<TESForm>(menuName, base->FormType, base);
#endif
	}

	void UnregisterForMenu(TESForm * base, BSFixedString menuName)
	{
		if (!base || !menuName.m_data)
			return;

		// PRINT_FMT("%p %s", base, menuName.c_str());

#if USE_SKSE_ADDON
		SKSE::MenuOpenCloseRegistrationMapHolder::GetSingleton()->Unregister<TESForm>(menuName, base->FormType, base);
#endif
	}

	void UnregisterForAllMenus(TESForm* base)
	{
		if (!base)
			return;

#if USE_SKSE_ADDON
		 SKSE::MenuOpenCloseRegistrationMapHolder::GetSingleton()->UnregisterAll<TESForm>(base->FormType, base);
#endif
	}

	void RegisterForModEvent(TESForm * base, BSFixedString eventName, BSFixedString callbackName)
	{
		if (!base || !eventName.m_data || !callbackName.m_data)
			return;

		// PRINT_FMT("%p %s", base, eventName.c_str(), callbackName.c_str());

#if USE_SKSE_ADDON
		SKSE::ModCallbackParameters params;
		params.m_callbackName = callbackName;
		SKSE::ModCallbackRegistrationMapHolder::GetSingleton()->Register<TESForm>(eventName, base->FormType, base, &params);
#endif
	}

	void UnregisterForModEvent(TESForm * base, BSFixedString eventName)
	{
		if (!base || !eventName.m_data)
			return;

		// PRINT_FMT("%p %s", base, eventName.c_str());

#if USE_SKSE_ADDON
		SKSE::ModCallbackRegistrationMapHolder::GetSingleton()->Unregister<TESForm>(eventName, base->FormType, base);
#endif
	}

	void SendModEvent(TESForm * base, BSFixedString eventName, BSFixedString strArg, float numArg)
	{
		if (!eventName.m_data)
			return;

		// PRINT_FMT("%p %s %s %f", base, eventName.c_str(), strArg.c_str(), numArg);

#if USE_SKSE_ADDON
		SKSE::ModCallbackEvent evn(eventName, strArg, numArg, base);
		SKSE::ModCallbackEventDispatcher::GetSingleton()->SendEventSink(&evn);
#endif
	}

	void RegisterForCameraState(TESForm * thisForm)
	{
		if(!thisForm)
			return;
	
#if USE_SKSE_ADDON
		SKSE::CameraEventRegistrationSetHolder::GetSingletion()->Register<TESForm>(thisForm->FormType, thisForm);
#endif
	}
	
	void UnregisterForCameraState(TESForm * thisForm)
	{
		if(!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::CameraEventRegistrationSetHolder::GetSingletion()->Unregister<TESForm>(thisForm->FormType, thisForm);
#endif
	}
	
	void RegisterForCrosshairRef(TESForm * thisForm)
	{
		if(!thisForm)
			return;
	
#if USE_SKSE_ADDON
		SKSE::CrosshairRefEventRegistrationSetHolder::GetSingletion()->Register<TESForm>(thisForm->FormType, thisForm);
#endif
	}
	
	void UnregisterForCrosshairRef(TESForm * thisForm)
	{
		if(!thisForm)
			return;
	
#if USE_SKSE_ADDON
		SKSE::CrosshairRefEventRegistrationSetHolder::GetSingletion()->Unregister<TESForm>(thisForm->FormType, thisForm);
#endif
	}
	
	void RegisterForActorAction(TESForm * thisForm, uint32_t actionType)
	{
		if(!thisForm)
			return;

		// PRINT_FMT("%p %d", thisForm, actionType);

#if USE_SKSE_ADDON
		SKSE::ActionEventRegistrationMapHolder::GetSingletion()->Register<TESForm>(actionType, thisForm->FormType, thisForm);
#endif
	}
	
	void UnregisterForActorAction(TESForm * thisForm, uint32_t actionType)
	{
		if(!thisForm)
			return;

		// PRINT_FMT("%p %d", thisForm, actionType);

#if USE_SKSE_ADDON
		SKSE::ActionEventRegistrationMapHolder::GetSingletion()->Unregister<TESForm>(actionType, thisForm->FormType, thisForm);
#endif
	}

	void RegisterForNiNodeUpdate(TESForm * thisForm)
	{
		if(!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::NinodeUpdateRegistrationSetHolder::GetSingletion()->Register<TESForm>(thisForm->FormType, thisForm);
#endif

	}
	
	void UnregisterForNiNodeUpdate(TESForm * thisForm)
	{
		if(!thisForm)
			return;

#if USE_SKSE_ADDON
		SKSE::NinodeUpdateRegistrationSetHolder::GetSingletion()->Unregister<TESForm>(thisForm->FormType, thisForm);
#endif

	}

	bool RegisterForm(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		//
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(GetKeywords), TESForm,		std::vector<BGSKeyword*>>							("GetKeywords",					"Form", GetKeywords));
		//

		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(GetFormType),				TESForm, uint32_t>									("GetType",						"Form", GetFormType));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(GetFormName),				TESForm, BSFixedString>								("GetName",						"Form", GetFormName));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(GetFormWeight),				TESForm, float>										("GetWeight",					"Form", GetFormWeight));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(GetFormValue),				TESForm, uint32_t>									("GetGoldValue",				"Form", GetFormValue));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(GetFormKeywordsCount),		TESForm, uint32_t>									("GetNumKeywords",				"Form", GetFormKeywordsCount));										     
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(FormIsPlayable),				TESForm, bool>										("IsPlayable",					"Form", FormIsPlayable));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(FormHasModel),				TESForm, bool>										("HasWorldModel",				"Form", FormHasModel));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(GetFormModel),				TESForm, BSFixedString>								("GetWorldModelPath",			"Form", GetFormModel));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(GetFormTextureCount),		TESForm, uint32_t>									("GetWorldModelNumTextureSets", "Form", GetFormTextureCount));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(SetFormName),				TESForm, void, BSFixedString>						("SetName",						"Form", SetFormName));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(SetFormWeight),				TESForm, void, float>								("SetWeight",					"Form", SetFormWeight));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(SetFormValue),				TESForm, void, uint32_t>							("SetGoldValue",				"Form", SetFormValue));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(GetFormKeywords),			TESForm, BGSKeyword*, uint32_t>						("GetNthKeyword",				"Form", GetFormKeywords));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(SetFormKnown),				TESForm, void,  bool>								("SetPlayerKnows",				"Form", SetFormKnown));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(SetFormModel),				TESForm, void, BSFixedString>						("SetWorldModelPath",			"Form", SetFormModel));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(GetFormTextureSet),			TESForm, BGSTextureSet*, uint32_t>					("GetWorldModelNthTextureSet",  "Form", GetFormTextureSet));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(SetFormModelTexture),		TESForm, void, BGSTextureSet*, uint32_t>			("SetWorldModelNthTextureSet",  "Form", SetFormModelTexture));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(RegisterForMenu),			TESForm, void, BSFixedString>						("RegisterForMenu",				"Form", RegisterForMenu));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(UnregisterForMenu),			TESForm, void, BSFixedString>						("UnregisterForMenu",			"Form", UnregisterForMenu));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(UnregisterForAllMenus),		TESForm, void>										("UnregisterForAllMenus",		"Form", UnregisterForAllMenus));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(RegisterForModEvent),		TESForm, void, BSFixedString, BSFixedString>		("RegisterForModEvent",			"Form", RegisterForModEvent));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(UnregisterForModEvent),		TESForm, void, BSFixedString>						("UnregisterForModEvent",		"Form", UnregisterForModEvent));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(SendModEvent),				TESForm, void, BSFixedString, BSFixedString, float> ("SendModEvent",				"Form", SendModEvent));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(UnregisterForAllKeys),		TESForm, void>										("UnregisterForAllKeys",		"Form", UnregisterForAllKeys));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(RegisterForKey),				TESForm, void, uint32_t>							("RegisterForKey",				"Form", RegisterForKey));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(UnregisterForKey),			TESForm, void, uint32_t>							("UnregisterForKey",			"Form", UnregisterForKey));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(UnregisterForAllControls),	TESForm, void>										("UnregisterForAllControls",	"Form", UnregisterForAllControls));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(RegisterForControl),			TESForm, void, BSFixedString>						("RegisterForControl",			"Form", RegisterForControl));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(UnregisterForControl),		TESForm, void, BSFixedString>						("UnregisterForControl",		"Form", UnregisterForControl));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(RegisterForCameraState),		TESForm, void>						                ("RegisterForCameraState",	    "Form", RegisterForCameraState));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(UnregisterForCameraState),	TESForm, void>						                ("UnregisterForCameraState",    "Form", UnregisterForCameraState));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(RegisterForCrosshairRef),	TESForm, void>						                ("RegisterForCrosshairRef",		"Form", RegisterForCrosshairRef));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(UnregisterForCrosshairRef),	TESForm, void>						                ("UnregisterForCrosshairRef",	"Form", UnregisterForCrosshairRef));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(RegisterForActorAction),		TESForm, void, uint32_t>		                    ("RegisterForActorAction",		"Form", RegisterForActorAction));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(UnregisterForActorAction),	TESForm, void, uint32_t>		                    ("UnregisterForActorAction",	"Form", UnregisterForActorAction));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(RegisterForNiNodeUpdate),	TESForm, void>										("RegisterForNiNodeUpdate",		"Form", RegisterForNiNodeUpdate));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction<false, NFDLSE(UnregisterForNiNodeUpdate),	TESForm, void>										("UnregisterForNiNodeUpdate",	"Form", UnregisterForNiNodeUpdate));

		VM->SetCallableFromTasklets("Form", "SetPlayerKnows",				 true);
		VM->SetCallableFromTasklets("Form", "HasWorldModel",				 true);
		VM->SetCallableFromTasklets("Form", "HasWorldModel",				 true);
		VM->SetCallableFromTasklets("Form", "RegisterForKey",				 true);
		VM->SetCallableFromTasklets("Form", "UnregisterForKey",				 true);
		VM->SetCallableFromTasklets("Form", "UnregisterForAllKeys",			 true);
		VM->SetCallableFromTasklets("Form", "RegisterForMenu",				 true);
		VM->SetCallableFromTasklets("Form", "UnregisterForMenu",			 true);
		VM->SetCallableFromTasklets("Form", "UnregisterForAllMenus",		 true);
		VM->SetCallableFromTasklets("Form", "RegisterForModEvent",			 true);
		VM->SetCallableFromTasklets("Form", "SendModEvent",					 true);
		VM->SetCallableFromTasklets("Form", "UnregisterForAllModEvents",	 true);
		VM->SetCallableFromTasklets("Form", "RegisterForControl",			 true);
		VM->SetCallableFromTasklets("Form", "UnregisterForControl",			 true);
		VM->SetCallableFromTasklets("Form", "UnregisterForAllControls",		 true);
		VM->SetCallableFromTasklets("Form", "RegisterForCameraState",		 true);
		VM->SetCallableFromTasklets("Form", "UnregisterForCameraState",		 true);
		VM->SetCallableFromTasklets("Form", "RegisterForCrosshairRef",		 true);
		VM->SetCallableFromTasklets("Form", "UnregisterForCrosshairRef",	 true);
		VM->SetCallableFromTasklets("Form", "RegisterForActorAction",		 true);
		VM->SetCallableFromTasklets("Form", "UnregisterForActorAction",		 true);

		return true;
	}
}