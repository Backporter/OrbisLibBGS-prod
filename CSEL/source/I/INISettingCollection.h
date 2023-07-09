#pragma once

#include "../../../OrbisUtil/include//Relocation.h"

#include "../S/Setting.h"
#include "../S/SettingCollectionList.h"

namespace ConsoleRE
{
	class INISettingCollection : public SettingCollectionList<Setting>
	{
	public:
		~INISettingCollection() override;

		// override
		bool WriteSetting(Setting* a_setting) override;
		bool ReadSetting(Setting* a_setting) override;
		bool OpenHandle(bool a_create) override;
		bool CloseHandle() override;

		static INISettingCollection* GetSingleton()
		{
			Relocation<INISettingCollection**> singleton("", 0x37DA410);
			return *singleton;
		}

		Setting* GetSetting(const char* a_name)
		{
			for (auto& setting : settings)
			{
				if (strlen(a_name) == strlen(setting->m_name) && !strcasecmp(a_name, setting->m_name))
				{
					return setting;
				}
			}

			return nullptr;
		}
	public:
	};
	static_assert(sizeof(INISettingCollection) == 0x128);
}