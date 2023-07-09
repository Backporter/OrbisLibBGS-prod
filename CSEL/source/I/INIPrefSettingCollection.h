#pragma once

#include "../I/INISettingCollection.h"

namespace ConsoleRE
{
	class INIPrefSettingCollection : public INISettingCollection
	{
	public:
		~INIPrefSettingCollection() override;
		
		// override
		void Unk_07(void) override;
		void Unk_08(void) override;
		void Unk_09(void) override;
		
		static SettingCollectionList* GetSingleton()
		{
			Relocation<INIPrefSettingCollection**> singleton("", 0x373BB28);
			return *singleton;
		}
	public:
	};
	static_assert(sizeof(INIPrefSettingCollection) == 0x128);
}