#pragma once

#include "../B/BSTCaseInsensitiveStringMap.h"

#include "../S/Setting.h"
#include "../S/SettingCollection.h"

namespace ConsoleRE
{
	template <typename T>
	class SettingCollectionMap : public SettingCollection<T>
	{
	public:
		~SettingCollectionMap() override;

		// override (SettingCollection<T>)
		void InsertSetting(T* a_setting) override;
		void RemoveSetting(T* a_setting) override;
		void Unk_08(void) override;
		void Unk_09(void) override;
	public:
		BSTCaseInsensitiveStringMap<T*> settings;
	};
}