#include "../Scaleform/ScaleformExt.h"

#include "../../../../../OrbisUtil/include/MessageHandler.h"

#include "../../../../source/G/GFxMovieRoot.h"
#include "../../../../source/G/GFxValue.h"

#include "ext\ScaleFormALL.h"

namespace Scaleform
{
	static std::list <Interface::ScaleformInterface::ScaleformPluginInfo> pluginList;
	static std::map<const std::type_info*, ConsoleRE::GFxFunctionHandler*> fnlist;

	bool RegisterScaleformCallback(const char* a_plugin, Interface::ScaleformInterface::CallBack_t* a_pluginCallback)
	{
		// check for a name collision
		for (auto iter = pluginList.begin(); iter != pluginList.end(); ++iter)
		{
			if (!strcmp(iter->GetPluginName(), a_plugin))
			{
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kModuleLog)->Write(xUtilty::Log::logLevel::kWarning, "ScaleForm plugin name collision: %s", iter->GetPluginName());
				return false;
			}
		}

		Interface::ScaleformInterface::ScaleformPluginInfo plugin;
		plugin.SetPluginName(a_plugin);
		plugin.SetPluginCalback(a_pluginCallback);

		pluginList.push_back(plugin);

		return true;
	}

	template <typename T>
	void RegisterFN(ConsoleRE::GFxValue* dst, ConsoleRE::GFxMovieRoot* view, const char* FN_name)
	{
		ConsoleRE::GFxFunctionHandler* FunctionPointer = NULL;

		auto f = fnlist.find(&typeid(T));
		if (f != fnlist.end())
		{
			FunctionPointer = f->second;
		}

		if (!FunctionPointer)
		{
			FunctionPointer = new T;
			fnlist[&typeid(T)] = FunctionPointer;
		}


		ConsoleRE::GFxValue fnval;
		view->CreateFunction(&fnval, FunctionPointer);

		dst->SetMember(FN_name, &fnval);
	}

	// since we hook the vtbl entry that is this function, we need to manually call it directly
	Relocation<void(*)(ConsoleRE::GFxMovieRoot*, uint32_t)> SetViewScaleMode("", 0x117A5C0);

	// this function uses SKSE names because mods still depend on it
	void RegisterNewScaleform(ConsoleRE::GFxMovieRoot* a_this, uint32_t unk)
	{
		ConsoleRE::GFxValue Global;
		ConsoleRE::GFxValue Version;
		ConsoleRE::GFxValue SKSE;
		ConsoleRE::GFxValue	Plugins;

		if (!a_this->GetVariable(&Global, "_global"))
		{
			xUtilty::KernelPrintOut("a_this->GetVariable(global, \"_global\" failed...");
			goto fnexit;
		}
		
		a_this->CreateObject(&Version);
		a_this->CreateObject(&SKSE);
		a_this->CreateObject(&Plugins);

		Version.RegisterNumber("major", 90);
		Version.RegisterNumber("minor", 90);
		Version.RegisterNumber("beta",	90);
		Version.RegisterNumber("releaseIdx", 90);
		
		RegisterFN<ScaleFormLastControll>				  (&SKSE, a_this, "GetLastControl");
		RegisterFN<ScaleFormLastKeyCode>				  (&SKSE, a_this, "GetLastKeycode");
		RegisterFN<ScaleformSetINISetting>				  (&SKSE, a_this, "SetINISetting");
		RegisterFN<ScaleformGetINISetting>				  (&SKSE, a_this, "GetINISetting");
		RegisterFN<ScaleFormLog>						  (&SKSE, a_this, "Log");
		RegisterFN<ScaleFormNotify>						  (&SKSE, a_this, "Notify");
		RegisterFN<ScaleformGetMappedKey>				  (&SKSE, a_this, "GetMappedKey");							  
		RegisterFN<ScaleformMenu<MenuType::Open>>		  (&SKSE, a_this, "OpenMenu");
		RegisterFN<ScaleformMenu<MenuType::Close>>		  (&SKSE, a_this, "CloseMenu");
		RegisterFN<ScaleformSEX<Mode::Get>>				  (&SKSE, a_this, "GetPlayerSex");
		RegisterFN<ScaleformAllowTextInput>			      (&SKSE, a_this, "AllowTextInput");
		RegisterFN<ScaleformGetModList>				      (&SKSE, a_this, "GetModList");
		RegisterFN<ScaleformSendModEvent>				  (&SKSE, a_this, "SendModEvent");
		RegisterFN<ScaleformStoreIndices>				  (&SKSE, a_this, "StoreIndices");
		RegisterFN<ScaleformLoadIndices>				  (&SKSE, a_this, "LoadIndices");
		RegisterFN<ScaleformRequestActivePlayerEffects>   (&SKSE, a_this, "RequestActivePlayerEffects");
		RegisterFN<ScaleformRequestActorValues>			  (&SKSE, a_this, "RequestActorValues");
		RegisterFN<ScaleformExtendAlchemyCategories>	  (&SKSE, a_this, "ExtendAlchemyCategories");
		RegisterFN<ScaleformEnableMapMenuMouseWheel>	  (&SKSE, a_this, "EnableMapMenuMouseWheel");
		RegisterFN<ScaleformForceContainerCategorization> (&SKSE, a_this, "ForceContainerCategorization");
		RegisterFN<ScaleformExtendData>					  (&SKSE, a_this, "ExtendData");
		RegisterFN<ScaleformExtendForm>					  (&SKSE, a_this, "ExtendForm");
		RegisterFN<ScaleformShowOnMap>					  (&SKSE, a_this, "ShowOnMap");
		RegisterFN<ScaleformStartRemapMode>				  (&SKSE, a_this, "StartRemapMode");

		for (auto iter = pluginList.begin(); iter != pluginList.end(); ++iter)
		{
			ConsoleRE::GFxValue	plugin;
			a_this->CreateObject(&plugin);

			auto s_callback = iter->GetPluginCallback();
			if (s_callback)
			{
				s_callback(a_this, &plugin);
			}

			Plugins.SetMember(iter->GetPluginName(), &plugin);
		}

		SKSE.SetMember	("plugins", &Plugins);
		SKSE.SetMember  ("version", &Version);
		Global.SetMember("skse",    &SKSE);
		
		goto fnexit;

	fnexit:
		SetViewScaleMode(a_this, unk);	
	}
}