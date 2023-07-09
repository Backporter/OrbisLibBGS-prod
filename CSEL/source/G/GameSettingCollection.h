#pragma once

#include "../S/Setting.h"
#include "../S/SettingCollectionMap.h"

namespace ConsoleRE
{
	class GameSettingCollection : public SettingCollectionMap<Setting>
	{
	public:
		~GameSettingCollection() override;

		// override (SettingCollectionMap<Setting>)
		bool WriteSetting(Setting* a_setting) override;
		bool ReadSetting(Setting* a_setting) override;
		bool OpenHandle(bool a_create) override;
		bool CloseHandle() override;

		// add
		virtual void Unk_0A();
		
		static GameSettingCollection* GetSingleton()
		{
			Relocation<GameSettingCollection**> singleton("", 0x30C9028);
			return *singleton;
		}

		Setting* GetSetting(const char* a_name)
		{
			return nullptr;
		}
	};
}