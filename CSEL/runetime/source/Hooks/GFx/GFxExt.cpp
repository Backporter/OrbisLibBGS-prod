#include "../GFx/GFxExt.h"

#include "../GFx/Ext/GFxLog.h"

#include "../../../../source/B/BSScaleformTranslator.h"
#include "../../../../source/I/INISettingCollection.h"

#include "../../../../../OrbisUtil/include/MessageHandler.h"
#include "../../../../../OrbisUtil/include/Relocation.h"
#include "../../../../../OrbisUtil/include/FileSystem.h"
#include "../../../../../OrbisUtil/include/Streams/IFIleStream.h"
#include "../../../../../OrbisUtil/include/SystemWrapper.h"
#include "../../../../../OrbisUtil/include/INIHandler.h"

#include "Translator.h"

namespace GFx
{
	// filename containing the ESP list..
	Relocation<char*> pluginList("", 0x18A7EBD);

	Relocation<ctor_t*> func;

	void RegisterGFx(ConsoleRE::GFxLoader*& a_this)
	{
		func(a_this);

		auto attr = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();

		if (attr->EnableGFxLogger)
		{
			a_this->SetState(ConsoleRE::GFxState::StateType::State_Log, new GFxLog());
		}

		auto translator = a_this->GetStateAddRef<ConsoleRE::BSScaleformTranslator>(ConsoleRE::GFxState::StateType::State_Translator);

		xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kDebug, "BSScaleformTranslator* translator -> %p", translator);

		size_t	stringlength = 0;
		char	string[260] { 0 };
		char	path[260] { 0 };
		
		//
		sprintf(path, "/app0/%s", pluginList.get());
		
		auto settingCollection = ConsoleRE::INISettingCollection::GetSingleton();
		auto setting = settingCollection ? settingCollection->GetSetting("sLanguage:General") : nullptr;
		auto sLanguage = setting ? setting->GetString() : "ENGLISH";

		// create a file stream with the plugin list file and read each plugin
		xUtilty::IFileStream pluginlist(path, xUtilty::IFileStream::kFlagReadMode);

		while (pluginlist.GetStreamPosition() < pluginlist.GetStreamCapacity())
		{
			// read the string and get only the extension to compare against known plugin extensions
			if ((stringlength = pluginlist.ReadString(string, nullptr, 260)) == -1)
				break;
			
			std::string plugin = string;
			auto extension = plugin.substr(plugin.size() - 4, 4);

			// confirm it's a plugin and not junk
			if (!strcasecmp(extension.c_str(), ".ESP") || !strcasecmp(extension.c_str(), ".ESM") || !strcasecmp(extension.c_str(), ".ESL"))
			{
				// take the string remove the extesnion and pass it to the function that will read the file.
				plugin = plugin.substr(0, plugin.size() - 4);
				ParseTranslation(plugin.c_str(), sLanguage, translator);
			}
		}

		if (attr->IsDebugMode)
		{
			translator->translator.translationMap.DumpHashMap();
		}
	}
}