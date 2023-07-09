#pragma once

#include "../B/BSTList.h"
#include "../S/SettingCollection.h"

#include "../../../OrbisUtil/include//Relocation.h"

namespace ConsoleRE
{
	template <typename T>
	class SettingCollectionList : public SettingCollection<T>
	{
	public:
		~SettingCollectionList() override;

		// override (SettingCollection<T>)
		void InsertSetting(T* a_setting) override;
		void RemoveSetting(T* a_setting) override;
		void Unk_08(void) override;
		void Unk_09(void) override;
	public:
		BSSimpleList<T*> settings;
	};
}