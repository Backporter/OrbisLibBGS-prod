#pragma once

#include "../T/TESCondition.h"
#include "../T/TESContainer.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSConstructibleObject : public TESForm
	{
	public:
		static constexpr int TypeID = 49;
	
		struct ConstructibleObjectData
		{
			uint16_t numConstructed;
		};
		static_assert(sizeof(ConstructibleObjectData) == 0x2);
	public:
		~BGSConstructibleObject() override;

		// override (TESForm)
		void InitializeData() override;
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
	public:
		TESContainer				requiredItems;
		TESCondition				conditions;
		TESForm*					createdItem;
		BGSKeyword*					benchKeyword;
		ConstructibleObjectData		data;
		uint16_t					pad52;
	};
	static_assert(sizeof(BGSConstructibleObject) == 0x58);
}